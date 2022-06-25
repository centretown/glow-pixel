// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "PixelMapper.h"

namespace glow
{
    class OrderedMapper : public PixelMapper
    {
    private:
        uint16_t begin;

    public:
        OrderedMapper(size_t length, uint16_t begin = 0)
            : PixelMapper(length), begin(begin) {}
        ~OrderedMapper() {}

        virtual uint16_t Get(uint16_t index)
        {
            // roll over if index exceeds length
            index %= length;
            return begin + index;
        }
    };
}
