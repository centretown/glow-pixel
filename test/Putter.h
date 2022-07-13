// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Color.h"
#include "PixelMapper.h"
#include "Controller.h"
#include "Sweeper.h"
#include "config.h"
#include "ColorPalette.h"
#include "wait.h"

// using glow::Spin;
using glow::Sweeper;
using pixel::color_pack;
using pixel::ColorPalette;
using pixel::Color;
using pixel::Controller;
using pixel::Device;
using pixel::PixelMapper;
using pixel::Pixels;

void clearPixels();

typedef struct
{
    PixelMapper *mapper;
    color_pack color;
    color_pack background;
    uint32_t ms = 100;
} ColorWrap;

class ColorSweeper : public Sweeper<ColorWrap &>
{
public:
    void Act(uint16_t i, ColorWrap &wrap)
    {
        color_pack color = (i % 2) ? wrap.color : wrap.background;
        Pixels.Put(wrap.mapper->Get(i), color);
        Pixels.Update();
        wait(wrap.ms);
    }
};

typedef struct
{
    uint32_t ms = 100;
    PixelMapper *mapper;
    ColorPalette *palette;
} PaletteWrap;

class PaletteSweeper : public Sweeper<PaletteWrap &>
{
public:
    void Act(uint16_t i, PaletteWrap &wrap)
    {
        Pixels.Put(wrap.mapper->Get(i), wrap.palette->Get(i));
        Pixels.Update();
        wait(wrap.ms);
    }
};

void putPalette(PixelMapper *mapper,
                ColorPalette *palette,
                bool reverse = false,
                uint32_t ms = 100);

void writeDevice(Device *device, color_pack packed,
                 uint32_t ms = 500);

void writeDevicePixel(Device *device, uint16_t offset,
                      color_pack packed, uint32_t ms = 20);

void writeController(Controller &controller,
                     Color &color);

void putMapper(PixelMapper *mapper, Color &color,
               bool reverse = false, uint32_t ms = 100);

void putGrid(PixelMapper *mapper, Color &even, Color &odd,
             bool reverse = false, uint32_t ms = 100);

void putController(PixelMapper *mapper,
                   Color &color, bool reverse = false);
