// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Grid.h"

namespace pixel
{
    class GridColumns : public Grid
    {
    public:
        GridColumns(range_pack range = 0, uint16_t columns = 1,
                    range_pack rows = 0, range_pack cols = 0)
            : Grid(range, columns, rows, cols) {}

        uint16_t Map(uint16_t index)
        {
            index -= Begin();
            Range r(rows);
            Range c(cols);

            auto row = (index % r.Length()) + r.Begin();
            auto col = (index / r.Length()) + c.Begin();

            return Begin() + (row * columns) + col;
        }
    };

} // namespace pixel
