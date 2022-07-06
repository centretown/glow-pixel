// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "PixelColorHSV.h"

namespace strip
{
    // void PixelColorHSV::fromRGB(PixelColor &color)
    // {
    //     const uint8_t cmax = findMax(color);
    //     const uint8_t cmin = findMin(color);
    //     const uint8_t delta = cmax - cmin;
    // }

    color_pack PixelColorHSV::RGB()
    {
        Adjusted adjusted;
        adjustSaturationValue(adjusted);
        uint16_t mappedHue = mapHue();
        color_pack colorPack = mapHueToColor(mappedHue);
        PixelColor color(colorPack);
        color.RGB(applySaturationValue(color.Red(), adjusted),
                  applySaturationValue(color.Green(), adjusted),
                  applySaturationValue(color.Blue(), adjusted));
        return color.Pack();
    }

} // namespace strip
