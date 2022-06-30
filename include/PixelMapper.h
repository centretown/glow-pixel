// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Mapper.h"
#include "SimpleRange.h"

using glow::Mapper;
using glow::SimpleRange;

namespace strip
{
    class PixelMapper : public Mapper<uint16_t>, public SimpleRange
    {
    protected:
        uint16_t current = 0;

    public:
        PixelMapper(uint16_t begin = 0, uint16_t end = 0)
            : SimpleRange(begin, end) {}
        PixelMapper(Range *range) : SimpleRange(range) {}
        virtual uint16_t Get(uint16_t index)
        {
            return index;
        };
    };
}
