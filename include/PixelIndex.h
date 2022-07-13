// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"

namespace pixel
{
    typedef struct
    {
        unsigned device : 4;  // 0 - 15
        unsigned offset : 12; // 0 - 1791
    } pixel_index;
} // namespace pixel
