// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "PixelColor.h"
#include "PixelMapper.h"
#include "PixelController.h"
#include "Sweeper.h"
#include "config.h"

using glow::Sweeper;
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
} Puttee;

class Putter : public Sweeper<Puttee *>
{
public:
    void Act(uint16_t i, Puttee *p)
    {
        Pixels.Put(p->mapper->Get(i), p->color);
        Pixels.Update();
        wait(p->ms);
    }
};
