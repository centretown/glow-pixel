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
    virtual void Put(uint16_t index, uint32_t color)
    {
        printf("Color:%u-%x\n", index, color);
    }
    virtual void Update()
    {
        printf("Update\n");
    }
};
#endif