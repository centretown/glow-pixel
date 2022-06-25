// Copyright (c) 2022 Dave Marsh. See LICENSE.
// This file copied part of the Adafruit_NeoPixel.h library.

#ifndef ARDUINO
#pragma once

#include "base.h"
#include "PixelWriter.h"

namespace glow
{
    class NativePixelWriter : public PixelWriter
    {
    public:
        NativePixelWriter(size_t length)
            : PixelWriter(length) {}

        virtual void Put(uint16_t index, PixelColor &color)
        {
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