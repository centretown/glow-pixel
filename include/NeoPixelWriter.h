// Copyright (c) 2022 Dave Marsh. See LICENSE.

#ifdef ARDUINO
#pragma once

#include "PixelWriter.h"
#include <Adafruit_NeoPixel.h>

namespace glow
{
    class NeoPixelWriter : public PixelWriter
    {
    private:
        Adafruit_NeoPixel &device;

    public:
        NeoPixelWriter(Adafruit_NeoPixel &device) : device(device)
        {
            length = device.numPixels();
        }
        ~NeoPixelWriter() {}

        virtual void Setup()
        {
            device.begin();
            device.clear();
            device.show();
        }

        virtual void Put(uint16_t index, PixelColor &color)
        {
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