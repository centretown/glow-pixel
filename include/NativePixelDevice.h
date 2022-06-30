// Copyright (c) 2022 Dave Marsh. See LICENSE.
// This file copied part of the Adafruit_NeoPixel.h library.

#ifndef ARDUINO
#pragma once

#include "base.h"
#include "PixelDevice.h"

namespace strip
{
    class NativePixelDevice : public PixelDevice
    {
    public:
        NativePixelDevice(uint16_t pixelCount)
            : PixelDevice(pixelCount) {}

        virtual void Put(uint16_t index, PixelColor &color)
        {
            index %= pixelCount;
            printf("Color:%u-%x:%x:%x\n", index, color.Red(),
                   color.Green(), color.Blue());
        }

        virtual void Update()
        {
            printf("Update\n");
        }
    };
}
#endif