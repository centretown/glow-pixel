// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once
#include "Range.h"

using glow::Range;

namespace pixel
{
    typedef enum : uint8_t
    {
        LINE,
        TRIANGLE,
        RECTANGLE,
        CIRCLE,
    } ShapeType;

    typedef enum : uint8_t
    {
        ROWS,
        COLUMNS,
    } Orientation;

    template <typename SHAPETYPE, typename ORIENTATION>
    class Shape
    {
    public:
    };
} // namespace pixel
