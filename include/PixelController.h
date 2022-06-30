// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "PixelMapper.h"
#include "PixelDevice.h"

using glow::SimpleRange;

namespace strip
{
    typedef uint16_t partition_type;
#define MAX_PIXEL_DEVICES ((sizeof(partition_type) * 8) - 1)
    // #define MAX_PIXEL_DEVICES 15

    class PixelController
    {
    private:
        PixelDevice **devices;
        uint8_t deviceCount = 0;
        uint16_t pixelCount = 0;
        SimpleRange range;

    private:
        PixelDevice *selectedDevice = NULL;
        partition_type selectedFlag = 0;
        partition_type partitions[MAX_PIXEL_DEVICES + 1] = {0};
        uint16_t selectedOffset = 0;
        uint8_t selectedIndex = 0;

    public:
        PixelController(PixelDevice **devices, uint8_t deviceCount);

        inline uint16_t PixelCount() { return pixelCount; }
        inline SimpleRange *Scope() { return &range; }

        void Setup();
        void Put(PixelMapper *mapper, PixelColor &color);
        void Put(uint16_t index, PixelColor &color);
        void Update();

    private:
        inline void select(uint16_t index)
        {
            for (selectedIndex = 0;
                 partitions[selectedIndex + 1] <= index;
                 selectedIndex++)
                ;
            selectedFlag |= 1 << selectedIndex;
            selectedOffset = index - partitions[selectedIndex];
            selectedDevice = devices[selectedIndex];
        }

        inline bool mustUpdate(size_t deviceIndex)
        {
            return ((1 << deviceIndex) & selectedFlag);
        }

        inline void updateDone() { selectedFlag = 0; }
    };
}
