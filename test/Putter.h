// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "PixelColor.h"
#include "PixelMapper.h"
#include "PixelController.h"
#include "Sweeper.h"
#include "config.h"
#include "ColorPalette.h"

using glow::Sweeper;
using strip::ColorPalette;
using strip::PixelColor;
using strip::PixelController;
using strip::PixelMapper;
using strip::Pixels;

void wait(uint32_t ms = 500);

typedef struct
{
    uint32_t ms = 100;
    PixelMapper *mapper;
    PixelColor color;
} ColorWrap;

class ColorSweeper : public Sweeper<ColorWrap *>
{
public:
    void Act(uint16_t i, ColorWrap *p)
    {
        Pixels.Put(p->mapper->Get(i), p->color);
        Pixels.Update();
        wait(p->ms);
    }
};

typedef struct
{
    uint32_t ms = 100;
    PixelMapper *mapper;
    ColorPalette *palette;
} PaletteWrap;

class PaletteSweeper : public Sweeper<PaletteWrap *>
{
public:
    void Act(uint16_t i, PaletteWrap *p)
    {
        Pixels.Put(p->mapper->Get(i), p->palette->Get(i));
        Pixels.Update();
        wait(p->ms);
    }
};
