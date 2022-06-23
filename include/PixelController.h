// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"
#include "config.h"
#include "PixelWriter.h"

namespace glow
{
    class PixelController
    {
    private:
        PixelWriter **writers;
        size_t length;
        size_t count = 0;

    public:
        PixelController(PixelWriter **writers, size_t length);
        ~PixelController() {}
        inline size_t Count() { return count; }

        void Setup();
        void Put(uint16_t index, PixelColor &color);
        void Update(uint16_t begin, uint16_t end);
    };
}