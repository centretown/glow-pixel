// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "Putter.h"

void putPalette(PixelMapper *mapper,
                ColorPalette *palette, bool reverse,
                uint32_t ms)
{
    PaletteWrap wrapper;
    wrapper.mapper = mapper;
    wrapper.palette = palette;
    wrapper.ms = ms;
    PaletteSweeper sweeper;

    sweeper.Sweep(mapper->Pack(), wrapper, reverse);
}

void writeDevice(Device *device, color_pack packed, uint32_t ms)
{
    uint16_t count = device->PixelCount();
    for (uint16_t i = 0; i < count; i++)
    {
        device->Put(i, packed);
    }
    device->Update();
    wait(ms);
}

void writeDevicePixel(Device *device, uint16_t offset,
                      color_pack packed, uint32_t ms)
{
    device->Put(offset, packed);
    device->Update();
    wait(ms);
}

void writeController(Controller &controller, Color &color)
{
    for (size_t i = 0; i < controller.PixelCount(); i++)
    {
        controller.Put(i, color.Pack());
    }
    controller.Update();
    wait();
}

void putController(PixelMapper *mapper, Color &color, bool reverse)
{
    Pixels.SweepColor(mapper, color.Pack(), reverse);
    Pixels.Update();
    wait();
}

void clearPixels()
{
    PixelMapper mapper(0, Pixels.PixelCount());
    Color backGround(0);
    Pixels.SweepColor(&mapper, backGround.Pack());
    Pixels.Update();
}

void putMapper(PixelMapper *mapper, Color &color, bool reverse, uint32_t ms)
{
    Color backGround(15, 15, 5);
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

void putGrid(PixelMapper *mapper, Color &even, Color &odd,
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
