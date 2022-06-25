// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "PixelMapper.h"

namespace glow
{
    class SegmentMapper : public PixelMapper
    {
    private:
        uint16_t begin;
        size_t length;

    public:
        SegmentMapper(uint16_t begin, size_t length)
            : begin(begin), length(length) {}
        ~SegmentMapper() {}

        virtual size_t Length() { return length; }
        virtual uint16_t Get(uint16_t index) { return begin + index; }
        virtual uint16_t Minimum() { return begin; }
    };
}
