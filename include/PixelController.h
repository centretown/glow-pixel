// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "PixelMapper.h"
#include "PixelDevice.h"
#include "Sweeper.h"

using glow::Range;
using glow::range_pack;
using glow::Sweeper;

namespace strip
{
    typedef uint16_t partition_type;
#define MAX_PIXEL_DEVICES ((sizeof(partition_type) * 8) - 1)
    // #define MAX_PIXEL_DEVICES 15

    class ColorSweep
    {
    public:
        PixelMapper *mapper;
        color_pack color;

    public:
        ColorSweep(PixelMapper *mapper, color_pack color)
            : mapper(mapper), color(color) {}
    };

    class PixelController
        : public Sweeper<ColorSweep &>
    {
    private:
        PixelDevice **devices;
        uint8_t deviceCount = 0;
        uint16_t pixelCount = 0;
        Range range;

    private:
        PixelDevice *selectedDevice = NULL;
        partition_type selectedFlag = 0;
        partition_type partitions[MAX_PIXEL_DEVICES + 1] = {0};
        uint16_t selectedOffset = 0;
        uint8_t selectedIndex = 0;

    public:
        PixelController(PixelDevice **devices, uint8_t deviceCount);

        inline uint16_t PixelCount() { return pixelCount; }
        inline range_pack Scope() { return range.Pack(); }

        void Setup();
        void SweepColor(PixelMapper *mapper, color_pack packed, bool reverse = false);
        void Put(uint16_t index, color_pack color);
        void Update();

        void Act(uint16_t index, ColorSweep &cs)
        {
            select(cs.mapper->Get(index));
            selectedDevice->Put(selectedOffset, cs.color);
        }

    private:
        inline void select(uint16_t index)
        {
            index %= pixelCount;
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
