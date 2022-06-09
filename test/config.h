// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#ifdef ARDUINO
#include "NeoPixelWriter.h"
Adafruit_NeoPixel strip19(19, 11, NEO_BRG + NEO_KHZ800);
Adafruit_NeoPixel strip15(15, 10, NEO_BRG + NEO_KHZ800);
Adafruit_NeoPixel strip4(4, 12, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip8(8, 13, NEO_GRB + NEO_KHZ800);
NeoPixelWriter writer(strip19);
#else
#include "NativePixelWriter.h"
NativePixelWriter writer;
#endif
