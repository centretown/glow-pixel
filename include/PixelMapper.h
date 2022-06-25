// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"

namespace glow
{
    class PixelMapper
    {
    protected:
        size_t length;

    public:
        PixelMapper(size_t length) : length(length) {}
        inline size_t Length() { return length; }
        virtual uint16_t Get(uint16_t index) = 0;
    };
}
