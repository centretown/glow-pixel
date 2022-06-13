// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"
#include "config.h"
#include "PixelWriter.h"

class PixelGroup
{
private:
    PixelWriter **writers;
    size_t length;
    size_t count = 0;

public:
    PixelGroup(PixelWriter **writers, size_t length);
    ~PixelGroup();
    inline size_t Count() { return count; }

    void Setup();
    void Put(uint16_t index, uint8_t red, uint8_t green, uint8_t blue);
    void Update(uint16_t begin, uint16_t end);
};
