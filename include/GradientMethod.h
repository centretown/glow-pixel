// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "PixelColorHSV.h"

namespace strip
{
    typedef enum : uint8_t
    {
        BY_HUE,
        BY_SATURATION,
        BY_VALUE,
    } GradientType;

    class GradientMethod
    {
    public:
        virtual uint16_t Span() = 0;
        virtual uint16_t Limit() = 0;
    };

} // namespace strip
