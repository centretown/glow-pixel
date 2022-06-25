// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "PixelWriter.h"
#define MAX_PIXEL_WRITERS 16

namespace glow
{
    typedef uint16_t PixelControllerUpdateFlag;

    class PixelController
    {
    private:
        PixelWriter **writers;
        size_t writerCount = 0;
        size_t pixelCount = 0;
        uint16_t updateFlag = 0;
        uint16_t partitions[MAX_PIXEL_WRITERS] = {0};

    public:
        PixelController(PixelWriter **writers, size_t length);

        inline size_t PixelCount() { return pixelCount; }

        void Setup();
        void Put(uint16_t index, PixelColor &color);
        void Update();

    private:
        inline size_t findWriterIndex(uint16_t index)
        {
            for (size_t i = 0; i < writerCount; i++)
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
