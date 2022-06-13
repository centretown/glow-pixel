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

    inline size_t Length()
    {
        return length;
    }

    virtual void Setup() {}
    virtual void Put(uint16_t index, uint8_t red, uint8_t green, uint8_t blue) = 0;
    virtual void Update() = 0;
};
