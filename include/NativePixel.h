// Copyright (c) 2022 Dave Marsh. See LICENSE.
// This file copied part of the Adafruit_NeoPixel.h library.

#ifndef ARDUINO
#pragma once

#include "base.h"
namespace strip
{
    class NativePixel
    {
    private:
        static const uint8_t _NeoPixelSineTable[256];

        /* Similar to above, but for an 8-bit gamma-correction table.
           Copy & paste this snippet into a Python REPL to regenerate:
        import math
        gamma=2.6
        for x in range(256):
            print("{:3},".format(int(math.pow((x)/255.0,gamma)*255.0+0.5))),
            if x&15 == 15: print
        */
        static const uint8_t _NeoPixelGammaTable[256];

    public:
        /*!
        @brief   Convert separate red, green and blue values into a single
               "packed" 32-bit RGB color.
        @param   r  Red brightness, 0 to 255.
        @param   g  Green brightness, 0 to 255.
        @param   b  Blue brightness, 0 to 255.
        @return  32-bit packed RGB value, which can then be assigned to a
               variable for later use or passed to the setPixelColor()
               function. Packed RGB format is predictable, regardless of
               LED strand color order.
        */
        static uint32_t Color(uint8_t r, uint8_t g, uint8_t b)
        {
            return ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
        }
        /*!
          @brief   Convert separate red, green, blue and white values into a
                   single "packed" 32-bit WRGB color.
          @param   r  Red brightness, 0 to 255.
          @param   g  Green brightness, 0 to 255.
          @param   b  Blue brightness, 0 to 255.
          @param   w  White brightness, 0 to 255.
          @return  32-bit packed WRGB value, which can then be assigned to a
                   variable for later use or passed to the setPixelColor()
                   function. Packed WRGB format is predictable, regardless of
                   LED strand color order.
        */
        static uint32_t Color(uint8_t r, uint8_t g, uint8_t b, uint8_t w)
        {
            return ((uint32_t)w << 24) | ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
        }
        static uint32_t ColorHSV(uint16_t hue, uint8_t sat = 255, uint8_t val = 255);
        /*!
          @brief   A gamma-correction function for 32-bit packed RGB or WRGB
                   colors. Makes color transitions appear more perceptially
                   correct.
          @param   x  32-bit packed RGB or WRGB color.
          @return  Gamma-adjusted packed color, can then be passed in one of the
                   setPixelColor() functions. Like gamma8(), this uses a fixed
                   gamma correction exponent of 2.6, which seems reasonably okay
                   for average NeoPixels in average tasks. If you need finer
                   control you'll need to provide your own gamma-correction
                   function instead.
        */

        static uint32_t gamma32(uint32_t x);
        static uint8_t sine8(uint8_t x)
        {
            return _NeoPixelSineTable[x]; // 0-255 in, 0-255 out
        }
        /*!
          @brief   An 8-bit gamma-correction function for basic pixel brightness
                   adjustment. Makes color transitions appear more perceptially
                   correct.
          @param   x  Input brightness, 0 (minimum or off/black) to 255 (maximum).
          @return  Gamma-adjusted brightness, can then be passed to one of the
                   setPixelColor() functions. This uses a fixed gamma correction
                   exponent of 2.6, which seems reasonably okay for average
                   NeoPixels in average tasks. If you need finer control you'll
                   need to provide your own gamma-correction function instead.
        */
        static uint8_t gamma8(uint8_t x)
        {
            return _NeoPixelGammaTable[x]; // 0-255 in, 0-255 out
        }

        // void rainbow(uint16_t first_hue = 0, int8_t reps = 1,
        //              uint8_t saturation = 255, uint8_t brightness = 255,
        //              bool gammify = true);
    };
}
#endif