// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"

namespace pixel
{
    class MatrixMapper
    {
    private:
        const uint16_t *matrix;
        const uint16_t size;

    public:
        MatrixMapper(const uint16_t *matrix, const uint16_t size)
            : matrix(matrix), size(size) {}

        inline uint16_t Map(uint16_t index)
        {
            if (index < size)
            {
                return matrix[index];
            }
            return index;
        };
    };
}
