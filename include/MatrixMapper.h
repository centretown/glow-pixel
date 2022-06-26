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
            : PixelMapper(pixelCount), matrix(matrix) {}

        virtual uint16_t Get(uint16_t index)
        {
            // roll over if index exceeds length
            index %= pixelCount;
            return matrix[index];
        }
    };
}
