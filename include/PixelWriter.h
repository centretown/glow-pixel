// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"
#include "PixelColor.h"

namespace glow
{
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
        virtual void Put(uint16_t index, PixelColor &color) = 0;
        virtual void Update() = 0;
    };
}