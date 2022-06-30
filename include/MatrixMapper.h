// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "PixelMapper.h"

namespace glow
{
    class MatrixMapper : public PixelMapper
    {
    private:
        const uint16_t *matrix;

    public:
        MatrixMapper(const uint16_t *matrix, uint16_t pixelCount)
            : matrix(matrix), PixelMapper(0, pixelCount) {}
        virtual uint16_t &Get(uint16_t index)
        {
            current = matrix[index];
            return current;
        };
    };
}
