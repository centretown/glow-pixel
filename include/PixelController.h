// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "PixelDevice.h"
#define MAX_PIXEL_DEVICES 16

namespace glow
{
    typedef uint16_t PixelControllerUpdateFlag;

    class PixelController
    {
    private:
        PixelDevice **devices;
        uint16_t deviceCount = 0;
        uint16_t pixelCount = 0;

        uint16_t updateFlag = 0;
        uint16_t partitions[MAX_PIXEL_DEVICES] = {0};

    public:
        PixelController(PixelDevice **writers, uint16_t length);

        inline uint16_t PixelCount() { return pixelCount; }

        void Setup();
        void Put(uint16_t index, PixelColor &color);
        void Update();

    private:
        inline size_t findWriterIndex(uint16_t index)
        {
            for (size_t i = 0; i < deviceCount; i++)
            {
                if (index < partitions[i])
                {
                    updateFlag |= 1 << i;
                    return i;
                }
            }
            return 0;
        }

        inline bool mustUpdate(size_t writerIndex)
        {
            return ((1 << writerIndex) & updateFlag);
        }

        inline void updateDone() { updateFlag = 0; }
    };
}
