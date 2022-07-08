// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"

namespace strip
{
    typedef enum : uint8_t
    {
        Complementary,
        Monochromatic,
        Analogous,
        Triadic,
        Tetradic,
    } Transition;
}
