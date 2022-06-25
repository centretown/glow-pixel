// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "PixelMapper.h"

namespace glow
{
    class MatrixMapper : public PixelMapper
    {
    private:
        const uint16_t *matrix;
        size_t length;

    public:
        MatrixMapper(size_t length, const uint16_t *matrix)
            : PixelMapper(length), matrix(matrix) {}

        virtual uint16_t Get(uint16_t index)
        {
            // roll over if index exceeds length
            index %= length;
            return matrix[index];
        }
    };
}
