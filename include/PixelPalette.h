// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "ColorFilter.h"

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

    class PixelWheel : public ColorFilter
    {
    private:
        uint16_t position = 0;

    public:
        PixelWheel(/* args */);
        ~PixelWheel();
        virtual PixelColor &Filter(PixelColor &source, PixelColor &color)
        {
            return color;
        }
    };
}

// // Input a value 0 to 255 to get a color value.
// // The colours are a transition r - g - b - back to r.
// uint32_t LedSegment::wheel(uint8_t pos)
// {
//     pos = 255 - pos;
//     if (pos < 85)
//     {
//         return ledWriter->Color(255 - pos * 3, 0, pos * 3);
//     }
//     if (pos < 170)
//     {
//         pos -= 85;
//         return ledWriter->Color(0, pos * 3, 255 - pos * 3);
//     }
//     pos -= 170;
//     return ledWriter->Color(pos * 3, 255 - pos * 3, 0);
// }
