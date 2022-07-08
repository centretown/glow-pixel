// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Mapper.h"
#include "Range.h"

using glow::Mapper;
using glow::Range;
using glow::range_pack;

namespace strip
{
    class PixelMapper : public Mapper<uint16_t>, public Range
    {
    public:
        PixelMapper(range_pack pack = 0) : Range(pack) {}

        PixelMapper(uint16_t begin, uint16_t end)
            : Range(begin, end) {}

        virtual uint16_t Get(uint16_t index)
        {
            return index;
        };
    };
}
