// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Range.h"

using glow::Range;
using glow::range_pack;

namespace pixel
{
    class Grid : public Range
    {
    protected:
        uint16_t rowLength;
        Range rows, cols;

    public:
        Grid(range_pack pack = 0, uint16_t rowLength = 1,
             range_pack rows = 0, range_pack cols = 0)
        {
            Resize(pack, rowLength, rows, cols);
        }

        Grid(Range &range, uint16_t rowLength,
             range_pack rows, range_pack cols)
        {
            Resize(range.Pack(), rowLength, rows, cols);
        }

        Grid(Grid *grid)
        {
            Copy(grid);
        }

        // access
        inline range_pack Rows() { return rows.Pack(); }
        inline range_pack Cols() { return cols.Pack(); }

        // modify all
        inline void Copy(Grid *grid)
        {
            Resize(grid->Pack(), grid->rowLength,
                   grid->rows.Pack(), grid->cols.Pack());
        }

        inline void Resize(range_pack r, range_pack c)
        {
            Resize(Pack(), rowLength, r, c);
        }

        inline void Resize(range_pack p, uint16_t rl,
                           range_pack r, range_pack c)
        {
            rowLength = rl;
            rows.Pack(r);
            cols.Pack(c);
            Pack(p);
            uint16_t end = Begin() +
                           rows.Length() * cols.Length();
            Range::Resize(Begin(), end);
        }
    };
} // namespace pixel
