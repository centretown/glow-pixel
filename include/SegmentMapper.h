// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "PixelMapper.h"

namespace glow
{
    class SegmentMapper : public PixelMapper
    {
    private:
        uint16_t begin;

    public:
        SegmentMapper(uint16_t begin, uint16_t pixelCount)
            : PixelMapper(pixelCount), begin(begin) {}
        ~SegmentMapper() {}

        virtual uint16_t Get(uint16_t index)
        {
            // roll over if index exceeds length
            index %= pixelCount;
            return begin + index;
        }
        uint16_t Begin() { return begin; }
        uint16_t End() { return begin + pixelCount; }
    };
}
