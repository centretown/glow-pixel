// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "GradientPalette.h"
#include "HueUpdater.h"
#include "Activity.h"

using color::VARY_HUE;
using glow::Range;
using glow::Activity;
using pixel::Grid;
using pixel::GRID_COLUMNS;
using pixel::GRID_ROWS;
using pixel::HueUpdater;

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

GradientPalette paletteA(VARY_HUE);
GradientPalette paletteB(VARY_HUE);

HueUpdater updaterA(gridA, paletteA, 50);
Activity activityA(&updaterA);

HueUpdater updaterB(gridB, paletteB, 500);
Activity activityB(&updaterB);
