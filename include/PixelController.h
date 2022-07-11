// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Sweeper.h"
#include "PixelIndex.h"
#include "PixelColor.h"
#include "PixelDevice.h"
#include "PixelMapper.h"

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
        const uint8_t deviceCount;
        const pixel_index *pixelIndex;
        const uint16_t pixelCount;
        Range range;

    private:
        partition_type selectedFlag = 0;

    public:
        PixelController(PixelDevice **devices, const uint8_t deviceCount,
                        const pixel_index *pixelIndex, const uint16_t pixelCount)
            : devices(devices), deviceCount(deviceCount),
              pixelIndex(pixelIndex), pixelCount(pixelCount)
        {
            range.Resize(0, pixelCount);
        }
        ~PixelController() {}

        inline uint16_t PixelCount() { return pixelCount; }
        inline range_pack Scope() { return range.Pack(); }

        void Setup();

        void SweepColor(PixelMapper *mapper, color_pack packed, bool reverse = false);
        inline void Put(uint16_t index, color_pack color)
        {
            if (index < pixelCount)
            {
                pixel_index px = pixelIndex[index];
                devices[px.device]->Put(px.offset, color);
                selectedFlag |= 1 << px.device;
            }
        }
        void Update();

        void Act(uint16_t index, ColorSweep &cs)
        {
            Put(index, cs.color);
        }

    private:
        inline bool mustUpdate(size_t deviceIndex)
        {
            return ((1 << deviceIndex) & selectedFlag);
        }

        inline void updateDone() { selectedFlag = 0; }
    };
}
