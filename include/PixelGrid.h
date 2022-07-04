// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "PixelMapper.h"
#include "config.h"

namespace strip
{
    typedef enum : uint8_t
    {
        BY_ROW,
        BY_COL,
        AS_RANGE,
    } GridOrder;

    class PixelGrid : public PixelMapper
    {
    private:
        uint16_t rowLength;
        SimpleRange *rows;
        SimpleRange *cols;
        GridOrder order = BY_ROW;

    public:
        PixelGrid(uint16_t begin, uint16_t end, uint16_t rowLength,
                   SimpleRange *rows, SimpleRange *cols)
        {
            Resize(begin, end, rowLength, rows, cols);
        }

        inline SimpleRange *Rows() { return rows; }
        inline SimpleRange *Cols() { return cols; }

        void Resize(uint16_t b, uint16_t e, uint16_t rl,
                    SimpleRange *r, SimpleRange *c)
        {
            SimpleRange::Resize(b, e);
            rowLength = rl;
            rows = r;
            cols = c;
        }

        virtual uint16_t Get(uint16_t index)
        {
            if (order == BY_ROW)
            {
                return GetByRow(index);
            }
            if (order == BY_COL)
            {
                return GetByCol(index);
            }
            return GetAsRange(index);
        }

        inline void Order(GridOrder v) { order = v; }
        inline GridOrder Order() { return order; }

        inline uint16_t GetAsRange(uint16_t index)
        {
            return PixelMapper::Get(index);
        }

        inline uint16_t GetByRow(uint16_t index)
        {
            index -= Begin();
            auto row = (index / cols->Length()) + rows->Begin();
            auto col = (index % cols->Length()) + cols->Begin();
            index = Begin() + (row * rowLength) + col;
            return index;
        };

        inline uint16_t GetByCol(uint16_t index)
        {
            index -= Begin();
            auto row = (index % rows->Length()) + rows->Begin();
            auto col = (index / rows->Length()) + cols->Begin();
            index = Begin() + (row * rowLength) + col;
            return index;
        };
    };
} // namespace strip
