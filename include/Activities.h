// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "GradientActivity.h"
#include "SlideActivity.h"

using glow::Range;
using pixel::GradientActivity;
using pixel::Grid;
using pixel::GRID_COLUMNS;
using pixel::GRID_ROWS;
using pixel::SlideActivity;

#ifdef NATIVE
Range rangeA(0, 36);
Grid gridA(rangeA.Pack(), 9, GRID_COLUMNS);
Range rangeB(36, 66);
Grid gridB(rangeB.Pack(), rangeB.Length(), GRID_ROWS);
#endif

#ifdef MEGAATMEGA2560
Range rangeA(0, 19);
Grid gridA(rangeA.Pack(), rangeA.Length(), GRID_ROWS);
Range rangeB(19, 34);
Grid gridB(rangeB.Pack(), rangeB.Length(), GRID_ROWS);
#endif

#ifdef ESP32
Range rangeA(0, 36);
Grid gridA(rangeA.Pack(), 9, GRID_COLUMNS);
Range rangeB(36, 66);
Grid gridB(rangeB.Pack(), rangeB.Length(), GRID_ROWS);
#endif

#ifdef XIAO
Range rangeA(0, 4);
Grid gridA(rangeA.Pack(), rangeA.Length(), GRID_ROWS);
Range rangeB(4, 8);
Grid gridB(rangeB.Pack(), rangeB.Length(), GRID_ROWS);
#endif

GradientPalette paletteA(
    VARY_HUE, hue_red, saturation_size, 7);
GradientPalette paletteB(
    VARY_HUE, hue_red, saturation_size, 7);

GradientActivity activityA(paletteA, gridA);
GradientActivity activityB(paletteB, gridB);
SlideActivity sliderA(gridA, paletteA, 500);
