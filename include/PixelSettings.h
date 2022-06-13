// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"
#include "PixelGroup.h"
#include "PixelColor.h"
#include "PixelDimmer.h"

class PixelSettings
{
protected:
    static PixelGroup *group;

protected:
    PixelColor color;
    PixelDimmer dimmer;

public:
    PixelSettings() {}

    inline uint8_t Red() { return dimmer.Dim(color.Red()); }
    inline uint8_t Green() { return dimmer.Dim(color.Green()); }
    inline uint8_t Blue() { return dimmer.Dim(color.Blue()); }
    inline uint8_t White() { return dimmer.Dim(color.White()); }
    inline PixelDimmer &Dimmer() { return dimmer; }
    inline PixelColor &Color() { return color; }

public:
    static void Setup(PixelGroup *g);
};
