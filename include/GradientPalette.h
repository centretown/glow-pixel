// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "ColorPalette.h"
#include "SimpleRange.h"

using glow::SimpleRange;

namespace strip
{
    typedef enum : uint8_t
    {
        BY_HUE,
        BY_SATURATION,
        BY_VALUE,
    } GradientMethod;

    class GradientPalette : public ColorPalette
    {
    private:
        uint16_t hue = 0;
        uint8_t saturation = 0;
        uint8_t value = 0;
        bool applyGamma = true;
        GradientMethod method = BY_HUE;
        SimpleRange range;

    public:
        GradientPalette(uint16_t hue = 0,
                        uint8_t saturation = 0,
                        uint8_t value = 0, bool applyGamma = true)
            : hue(hue), saturation(saturation), value(value),
              applyGamma(applyGamma) {}

        inline uint16_t Hue() { return hue; }
        inline uint8_t Saturation() { return saturation; }
        inline uint8_t Value() { return value; }
    };

} // namespace strip

/*!
  @brief   Fill NeoPixel strip with one or more cycles of hues.
           Everyone loves the rainbow swirl so much, now it's canon!
  @param   first_hue   Hue of first pixel, 0-65535, representing one full
                       cycle of the color wheel. Each subsequent pixel will
                       be offset to complete one or more cycles over the
                       length of the strip.
  @param   reps        Number of cycles of the color wheel over the length
                       of the strip. Default is 1. Negative values can be
                       used to reverse the hue order.
  @param   saturation  Saturation (optional), 0-255 = gray to pure hue,
                       default = 255.
  @param   brightness  Brightness/value (optional), 0-255 = off to max,
                       default = 255. This is distinct and in combination
                       with any configured global strip brightness.
  @param   gammify     If true (default), apply gamma correction to colors
                       for better appearance.
*/
// void Adafruit_NeoPixel::rainbow(uint16_t first_hue, int8_t reps,
//   uint8_t saturation, uint8_t brightness, bool gammify) {
//   for (uint16_t i=0; i<numLEDs; i++) {
//     uint16_t hue = first_hue + (i * reps * 65536) / numLEDs;
//     uint32_t color = ColorHSV(hue, saturation, brightness);
//     if (gammify) color = gamma32(color);
//     setPixelColor(i, color);
//   }
// }
