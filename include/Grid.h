// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Range.h"
#include "Shape.h"

using glow::Range;
using glow::range_pack;

namespace pixel
{

    class Grid : public Range
    {
    protected:
        uint16_t columns;
        range_pack rows, cols;

    public:
        Grid(range_pack range, uint16_t columns,
             range_pack rows, range_pack cols)
        {
            Resize(range, columns, rows, cols);
        }

        // access
        inline range_pack Rows() { return rows; }
        inline range_pack Cols() { return cols; }

        inline void Resize(range_pack r, range_pack c)
        {
            Resize(Pack(), columns, r, c);
        }

        // modify
        inline range_pack Resize(range_pack range, uint16_t colCount,
                                 range_pack rowsRange, range_pack colsRange)
        {
            columns = colCount;
            rows = rowsRange;
            cols = colsRange;
            return Pack(range);
        }

        // implement
        inline uint16_t Map(uint16_t index)
        {
            index -= Begin();
            Range r(rows);
            Range c(cols);

            // uint16_t row = (index / c.Length()) + r.Begin();
            // uint16_t col = (index % c.Length()) + c.Begin();

            // return Begin() + (row * columns) + col;
            return index;
        }
    };
} // namespace pixel
