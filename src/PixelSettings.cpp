// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "PixelSettings.h"

PixelGroup *PixelSettings::group = NULL;
void PixelSettings::Setup(PixelGroup *g)
{
    group = g;
}
