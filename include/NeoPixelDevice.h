// Copyright (c) 2022 Dave Marsh. See LICENSE.

#ifdef ARDUINO
#pragma once

#include "PixelDevice.h"
#include <Adafruit_NeoPixel.h>

namespace strip
{
    class NeoPixelDevice : public PixelDevice
    {
    private:
        Adafruit_NeoPixel &device;

    public:
        NeoPixelDevice(Adafruit_NeoPixel &device)
            : PixelDevice(0), device(device)
        {
            pixelCount = device.numPixels();
        }

        virtual void Setup()
        {
            device.begin();
            device.clear();
            device.show();
        }

        virtual void Put(uint16_t index, PixelColor &color)
        {
            index %= pixelCount;
            device.setPixelColor(index, color.Red(),
                                 color.Green(), color.Blue());
        }

        virtual void Update()
        {
            device.show();
        }
    };
}
#endif