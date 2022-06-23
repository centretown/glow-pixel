// Copyright (c) 2022 Dave Marsh. See LICENSE.

#ifndef ARDUINO
#pragma once

#include "base.h"
#include "PixelWriter.h"

namespace glow
{
    class NativePixelWriter : public PixelWriter
    {
    public:
        NativePixelWriter(size_t size = 4096)
        {
            length = size;
        }

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