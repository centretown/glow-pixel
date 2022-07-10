// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "Putter.h"

void putPalette(PixelMapper *mapper,
                ColorPalette *palette,
                uint32_t ms)
{
    PixelColor backGround(15, 15, 5);
    Pixels.SweepColor(mapper, backGround.Pack());
    Pixels.Update();

    PaletteWrap wrapper;
    wrapper.mapper = mapper;
    wrapper.palette = palette;
    wrapper.ms = ms;
    PaletteSweeper sweeper;

    sweeper.Sweep(mapper->Pack(), wrapper);

    wait(1000);
    clearPixels();
}

void writeController(PixelController &controller, PixelColor &color)
{
    for (size_t i = 0; i < controller.PixelCount(); i++)
    {
        controller.Put(i, color.Pack());
    }
    controller.Update();
    wait();
}

void putController(PixelMapper *mapper, PixelColor &color, bool reverse)
{
    Pixels.SweepColor(mapper, color.Pack(), reverse);
    Pixels.Update();
    wait();
}

void wait(uint32_t ms)
{
#ifdef ARDUINO
    delay(ms);
#endif
}

void clearPixels()
{
    PixelMapper mapper(0, Pixels.PixelCount());
    PixelColor backGround(0, 0, 0);
    Pixels.SweepColor(&mapper, backGround.Pack());
    Pixels.Update();
}

void putMapper(PixelMapper *mapper, PixelColor &color, bool reverse, uint32_t ms)
{
    PixelColor backGround(15, 15, 5);
    Pixels.SweepColor(mapper, backGround.Pack(), reverse);
    Pixels.Update();

    ColorWrap puttee;
    puttee.mapper = mapper;
    puttee.color = color.Pack();
    puttee.background = color.Pack();
    puttee.ms = ms;
    ColorSweeper putter;

    putter.Sweep(mapper->Pack(), puttee, reverse);

    wait(1000);
    clearPixels();
}

void putGrid(PixelMapper *mapper, PixelColor &even, PixelColor &odd,
             bool reverse, uint32_t ms)
{
    ColorWrap puttee;
    puttee.mapper = mapper;
    puttee.color = even.Pack();
    puttee.background = odd.Pack();
    puttee.ms = ms;
    ColorSweeper putter;

    putter.Sweep(mapper->Pack(), puttee, reverse);

    wait(250);
    clearPixels();
}
