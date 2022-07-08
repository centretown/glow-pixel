// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "PixelGrid.h"

namespace strip
{
    class PixelRows : public PixelGrid
    {
    public:
        PixelRows(range_pack pack, uint16_t rowLength,
                  range_pack rows, range_pack cols)
            : PixelGrid(pack, rowLength, rows, cols) {}

        PixelRows(Range &range, uint16_t rowLength,
                  range_pack rows, range_pack cols)
            : PixelGrid(range, rowLength, rows, cols) {}

        virtual uint16_t Get(uint16_t index)
        {
            index -= Begin();
            auto row = (index / cols.Length()) + rows.Begin();
            auto col = (index % cols.Length()) + cols.Begin();
            index = Begin() + (row * rowLength) + col;
            return index;
        }
    };

} // namespace strip
