// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"

namespace glow
{
    class PixelMapper
    {
    public:
        virtual uint16_t Minimum() = 0;
        virtual size_t Length() = 0;
        virtual uint16_t Get(uint16_t index) = 0;
    };
}
