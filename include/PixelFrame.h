// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "PixelMapper.h"

namespace strip
{
    class PixelFrame : public PixelMapper
    {
    private:
        SimpleRange frame;
        uint16_t rows = 1;
        uint16_t cols = 1;

    public:
        PixelFrame(Range *parent, uint16_t rows)
            : PixelMapper(), rows(rows)
        {
            Copy(parent);
            frame.Copy(parent);
            Resize();
        }

        inline uint16_t Rows() { return rows; }
        inline uint16_t Cols() { return cols; }
        inline void Resize()
        {
            cols = (End() - Begin()) / rows;
        }

        // virtual uint16_t Get(uint16_t index)
        // {
        //     auto row = Begin() + (index / cols);
        //     auto col = index % cols;
        //     return (row * cols) + col;
        // };

        virtual uint16_t Get(uint16_t index)
        {
            auto row = index % rows;
            auto col = index / rows;
            return frame.Begin() + (row * cols) + col;
        };
    };
} // namespace strip
