// Copyright (c) 2022 Dave Marsh. See LICENSE.

#ifndef ARDUINO
#pragma once

#include "base.h"
#include "PixelWriter.h"

class NativePixelWriter : public PixelWriter
{
public:
    NativePixelWriter(size_t size = 4096)
    {
        length = size;
    }
    ~NativePixelWriter() {}
    virtual void Put(uint16_t index, uint8_t red, uint8_t green, uint8_t blue)
    {
        printf("Color:%u-%x:%x:%x\n", index, red, green, blue);
    }
    virtual void Update()
    {
        printf("Update\n");
    }
};
#endif