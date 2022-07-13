// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "PixelDevice.h"
#include "Sweeper.h"
#include "PixelIndex.h"
#include "Color.h"
#include "PixelMapper.h"

using glow::Range;
using glow::range_pack;
using glow::Sweeper;

namespace pixel
{
    class ColorSweep
    {
    public:
        PixelMapper *mapper;
        color_pack color;

    public:
        ColorSweep(PixelMapper *mapper, color_pack color)
            : mapper(mapper), color(color) {}
    };

    class Controller : public Sweeper<ColorSweep &>,
                       public Range
    {
    private:
        Device *devices;
        const uint8_t deviceCount;
        const pixel_index *pixelIndex;
        const uint16_t pixelCount;

    private:
        uint16_t selectedFlag = 0;

    public:
        Controller(Device *devices, const uint8_t deviceCount,
                   const pixel_index *pixelIndex, const uint16_t pixelCount)
            : Range(0, pixelCount),
              devices(devices), deviceCount(deviceCount),
              pixelIndex(pixelIndex), pixelCount(pixelCount)
        {
        }
        ~Controller() {}

        inline uint16_t PixelCount() { return pixelCount; }
        inline range_pack Scope() { return Pack(); }

        void Setup()
        {
            for (uint8_t i = 0; i < deviceCount; i++)
            {
                devices[i].Setup();
            }
        }

        Device &device(uint8_t i) { return devices[i]; }
        inline uint8_t device_count() { return deviceCount; }

        inline void SweepColor(PixelMapper *mapper, color_pack color,
                               bool reverse = false)
        {
            ColorSweep colorSweep(mapper, color);
            Sweep(mapper->Pack(), colorSweep);
        }

        inline void Put(uint16_t index, color_pack color)
        {
            if (index < pixelCount)
            {
                pixel_index px = pixelIndex[index];
                devices[px.device].Put(px.offset, color);
                selectedFlag |= 1 << px.device;
            }
        }

        inline void Update()
        {
            for (uint16_t i = 0; i < deviceCount; i++)
            {
                if (mustUpdate(i))
                {
                    devices[i].Update();
                }
            }
            updateDone();
        }

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
