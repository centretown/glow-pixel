// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Grid.h"

namespace pixel
{
    class GridRows : public Grid
    {
    public:
        GridRows(range_pack range = 0, uint16_t columns = 1,
                 range_pack rows = 0, range_pack cols = 0)
            : Grid(range, columns, rows, cols) {}

        inline uint16_t Map(uint16_t index)
        {
            index -= Begin();
            Range r(rows);
            Range c(cols);

            uint16_t row = (index / c.Length()) + r.Begin();
            uint16_t col = (index % c.Length()) + c.Begin();

            return Begin() + (row * columns) + col;
        }
    };

} // namespace pixel
