// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "PixelMapper.h"
#include "config.h"

namespace strip
{
    typedef enum : uint8_t
    {
        AS_ROWS,
        AS_COLS,
        AS_RANGE,
    } Orientation;

    class PixelFrame : public PixelMapper
    {
    private:
        uint16_t rowLength;
        SimpleRange *rows;
        SimpleRange *cols;
        Orientation orientation = AS_ROWS;

    private:
        static SimpleRange *global;

    public:
        PixelFrame(uint16_t begin, uint16_t end, uint16_t rowLength,
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
            if (orientation == AS_ROWS)
            {
                return GetAsRows(index);
            }
            if (orientation == AS_COLS)
            {
                return GetAsCols(index);
            }
            return GetAsRange(index);
        }

        inline void Orient(Orientation v) { orientation = v; }
        inline Orientation Orient() { return orientation; }

        inline uint16_t GetAsRange(uint16_t index)
        {
            return PixelMapper::Get(index);
        }

        inline uint16_t GetAsRows(uint16_t index)
        {
            index -= Begin();
            auto row = (index / cols->Length()) + rows->Begin();
            auto col = (index % cols->Length()) + cols->Begin();
            index = Begin() + (row * rowLength) + col;
            return index;
        };

        inline uint16_t GetAsCols(uint16_t index)
        {
            // auto row = Begin() + index % rows;
            // auto col = index / rows;
            return index;
        };
    };
} // namespace strip
