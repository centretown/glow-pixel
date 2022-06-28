// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "MatrixMapper.h"

namespace glow
{
    MatrixMapper::MatrixMapper(const uint16_t *matrix, uint16_t pixelCount)
        : PixelMapper(pixelCount), matrix(matrix)
    {
        for (uint16_t i = 0; i < pixelCount; i++)
        {
            uint16_t v = matrix[i];
            if (begin > v)
            {
                begin = v;
            }
            if (end < v)
            {
                end = v;
            }
        }
    }
}