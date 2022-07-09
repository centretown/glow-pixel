// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "PixelColor.h"
#include "PixelMapper.h"
#include "PixelController.h"
#include "Sweeper.h"
#include "config.h"
#include "ColorPalette.h"
#include "Looper.h"

using glow::Sweeper;
using strip::color_pack;
using strip::ColorPalette;
using strip::PixelColor;
using strip::PixelController;
using strip::PixelMapper;
using strip::Pixels;

void wait(uint32_t ms = 500);
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
                uint32_t ms = 100);

void writeController(PixelController &controller,
                     PixelColor &color);

void putMapper(PixelMapper *mapper, PixelColor &color,
               bool reverse = false, uint32_t ms = 100);

void putGrid(PixelMapper *mapper, PixelColor &even, PixelColor &odd,
             bool reverse = false, uint32_t ms = 100);

void putController(PixelMapper *mapper,
                   PixelColor &color, bool reverse = false);
