// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Range.h"
#include "Color.h"
#include "PixelIndex.h"

using glow::Range;
using glow::range_pack;

using color::Color;
using color::color_pack;

#ifdef ARDUINO
#include <Adafruit_NeoPixel.h>
#else
#include "NativeDevice.h"
#endif

namespace pixel
{
    template <typename DRIVER>
    class PixelDevice : Range
    {
    private:
        DRIVER &driver;
        const uint16_t pixelCount;
        Color color;

    public:
        PixelDevice(DRIVER &driver)
            : Range(0, driver.numPixels()), driver(driver),
              pixelCount(driver.numPixels()) {}

        inline const uint16_t PixelCount() { return pixelCount; }
        inline const range_pack Scope() { return Pack(); }

        inline void Setup()
        {
            driver.begin();
            driver.clear();
            driver.show();
        }

        inline void Put(uint16_t index, color_pack pack)
        {
            color.Pack(pack);
            driver.setPixelColor(index, color.Red(),
                                 color.Green(), color.Blue());
        }

        inline color_pack Get(uint16_t index)
        {
            return (color_pack)driver.getPixelColor(index);
        }

        inline void Update()
        {
            driver.show();
        }
    };
#ifdef ARDUINO
    typedef PixelDevice<Adafruit_NeoPixel> Device;
#else
    typedef PixelDevice<NativeDevice> Device;
#endif
} // namespace pixel