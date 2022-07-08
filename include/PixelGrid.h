// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "PixelMapper.h"
#include "config.h"

namespace strip
{
    class PixelGrid : public PixelMapper
    {
    protected:
        uint16_t rowLength;
        Range rows, cols;

    public:
        PixelGrid(range_pack pack, uint16_t rowLength,
                  range_pack rows, range_pack cols)
        {
            Resize(pack, rowLength, rows, cols);
        }

        PixelGrid(Range &range, uint16_t rowLength,
                  range_pack rows, range_pack cols)
        {
            Resize(range.Pack(), rowLength, rows, cols);
        }

        inline range_pack Rows() { return rows.Pack(); }
        inline range_pack Cols() { return cols.Pack(); }

        inline void Resize(range_pack p, uint16_t rl,
                           range_pack r, range_pack c)
        {
            Pack(p);
            rowLength = rl;
            rows.Pack(r);
            cols.Pack(c);
        }
    };
} // namespace strip
