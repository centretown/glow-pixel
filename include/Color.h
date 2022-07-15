// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"
#include "pixel_base.h"

namespace pixel
{
    typedef uint32_t color_pack;

    typedef enum : uint8_t
    {
        COLOR_BLUE,
        COLOR_GREEN,
        COLOR_RED,
        COLOR_WHITE,
    } PRIMARY;

    typedef struct
    {
        uint8_t blue;
        uint8_t green;
        uint8_t red;
        uint8_t white;
    } color_rgbw;

    typedef struct
    {
        uint8_t element;
        operator uint8_t() { return element; }
        inline uint8_t operator=(uint8_t &v)
        {
            return element = v;
        }
        inline uint8_t operator=(const uint8_t v)
        {
            return element = v;
        }
        inline uint8_t &operator&=(uint8_t v)
        {
            return element &= v;
        }
        inline uint8_t &operator|=(uint8_t v)
        {
            return element |= v;
        }
        inline uint8_t &operator^=(uint8_t v)
        {
            return element ^= v;
        }
        inline uint8_t operator&(uint8_t v) const
        {
            return element & v;
        }
        inline uint8_t operator|(uint8_t v) const
        {
            return element | v;
        }
        inline uint8_t operator^(uint8_t v) const
        {
            return element ^ v;
        }
        inline uint8_t operator>>(uint8_t v)
        {
            return element >> v;
        }
    } color_element;

    class Color
    {
    private:
        union
        {
            color_rgbw rgbw;
            color_pack pack;
            color_element elements[4];
        };

    public:
        Color(color_pack pack = 0) : pack(pack) {}

        Color(uint8_t red, uint8_t green,
              uint8_t blue, uint8_t white = 0)
        {
            RGBW(red, green, blue, white);
        }

        Color(Color &color)
        {
            Pack(color.Pack());
        }

        // access member

        inline uint8_t Red() const { return rgbw.red; }
        inline uint8_t Green() const { return rgbw.green; }
        inline uint8_t Blue() const { return rgbw.blue; }
        inline uint8_t White() const { return rgbw.white; }
        inline color_pack Pack() const { return pack; }

        // modify member

        // inline color_element &Element(PRIMARY i) { return elements[i]; }
        inline color_element &RED() { return elements[COLOR_RED]; }
        inline color_element &GREEN() { return elements[COLOR_GREEN]; }
        inline color_element &BLUE() { return elements[COLOR_BLUE]; }
        inline color_element &WHITE() { return elements[COLOR_WHITE]; }

        inline void Red(uint8_t r) { rgbw.red = r; }
        inline void Green(uint8_t g) { rgbw.green = g; }
        inline void Blue(uint8_t b) { rgbw.blue = b; }
        inline void White(uint8_t w) { rgbw.white = w; }

        // modify all operators
        inline Color &operator=(const Color &other)
        {
            Pack(other.Pack());
            return *this;
        }

        inline Color &operator=(const color_pack other)
        {
            Pack(other);
            return *this;
        }

        inline color_pack operator()() const
        {
            return pack;
        }

        inline color_pack operator()(color_pack v)
        {
            pack = v;
            return pack;
        }

        inline Color &operator()(int8_t r,
                                 int8_t g,
                                 int8_t b,
                                 int8_t w = 0)
        {
            RGBW(r, g, b, w);
            return *this;
        }

        inline color_pack AND(uint8_t mask)
        {
            return Color(RED() &= mask,
                         GREEN() &= mask,
                         BLUE() &= mask,
                         WHITE() &= mask)
                .Pack();
        }
        inline color_pack OR(int8_t mask)
        {
            return Color(RED() |= mask,
                         GREEN() |= mask,
                         BLUE() |= mask,
                         WHITE() |= mask)
                .Pack();
        }
        inline color_pack XOR(int8_t mask)
        {
            return Color(RED() ^= mask,
                         GREEN() ^= mask,
                         BLUE() ^= mask,
                         WHITE() ^= mask)
                .Pack();
        }

        inline color_pack operator&(int8_t mask)
        {
            return AND(mask);
        }

        inline color_pack operator|(int8_t mask)
        {
            return OR(mask);
        }

        inline color_pack operator^(int8_t mask)
        {
            return XOR(mask);
        }

        inline Color &operator&=(int8_t mask)
        {
            Pack(AND(mask));
            return *this;
        }

        inline Color &operator|=(int8_t mask)
        {
            Pack(OR(mask));
            return *this;
        }

        inline Color &operator^=(int8_t mask)
        {
            Pack(XOR(mask));
            return *this;
        }

        // modify all members

        inline void Pack(color_pack v) { pack = v; }

        inline void RGB(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0)
        {
            RGBW(r, g, b);
        }
        inline void GBR(uint8_t g = 0, uint8_t b = 0, uint8_t r = 0)
        {
            RGBW(r, g, b);
        }
        inline void BGR(uint8_t b = 0, uint8_t g = 0, uint8_t r = 0)
        {
            RGBW(r, g, b);
        }

        inline void RGBW(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0, uint8_t w = 0)
        {
            rgbw.red = r;
            rgbw.green = g;
            rgbw.blue = b;
            rgbw.white = w;
        }

        inline void Hue(uint16_t hue, uint8_t saturation = 255, uint8_t value = 255)
        {
            Pack(base_hsv(hue, saturation, value));
        }

        // filter functions (modify all)
        inline void Copy(Color &color)
        {
            Pack(color.Pack());
        }

        inline void Gamma(Color &color)
        {
            rgbw.red = gamma8(color.rgbw.red);
            rgbw.green = gamma8(color.rgbw.green);
            rgbw.blue = gamma8(color.rgbw.blue);
            rgbw.white = gamma8(color.rgbw.white);
        }

        inline void Sine(Color &color)
        {
            rgbw.red = sine8(color.rgbw.red);
            rgbw.green = sine8(color.rgbw.green);
            rgbw.blue = sine8(color.rgbw.blue);
            rgbw.white = sine8(color.rgbw.white);
        }

        inline uint32_t base_pack(uint8_t r, uint8_t g, uint8_t b, uint8_t w)
        {
            return _basePixel::Color(r, g, b, w);
        }

    private:
        inline uint32_t base_hsv(uint16_t hue, uint8_t saturation = 255, uint8_t value = 255)
        {
            return _basePixel::ColorHSV(hue, saturation, value);
        }
        inline uint8_t gamma8(uint8_t c)
        {
            return _basePixel::gamma8(c);
        }
        inline uint8_t sine8(uint8_t c)
        {
            return _basePixel::sine8(c);
        }
    };
}