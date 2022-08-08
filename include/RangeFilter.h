// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Filter.h"
#include "Range.h"
#include "Grid.h"
#include "Controller.h"
#include "Palette.h"

extern pixel::Controller &Pixels;
using glow::Filter;
using glow::Range;
using glow::range_pack;

using color::Palette;

namespace pixel
{
    class RangeFilter : public Filter<Palette>
    {
    private:
        Range range;
        Range section;

    public:
        virtual void Setup(range_pack scope, uint16_t section_length = 3)
        {
            range(scope);
            section(range.Begin(), range.Begin() + section_length);
        }

    private:
        virtual void apply(Palette &source)
        {
            section.SpinValues(Pixels, section, source);
            section >>= 3;
            if (section.End() > range.End())
            {
                section(range.Begin(), range.Begin() + section.Length());
            }
        }
    };

} // namespace pixel
