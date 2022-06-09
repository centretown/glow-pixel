// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"

class PixelWriter
{
protected:
    size_t length = 0;

public:
    PixelWriter() {}
    ~PixelWriter() {}

    virtual void Put(uint16_t index, uint32_t color) = 0;
    virtual void Update() = 0;

    virtual void Setup() {}

    virtual uint32_t Color(uint8_t red, uint8_t green, uint8_t blue)
    {
        return ((uint32_t)red << 16) | ((uint32_t)green << 8) | blue;
    }
    inline size_t Length()
    {
        return length;
    }
};
