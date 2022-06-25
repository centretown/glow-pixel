// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#ifdef ARDUINO
#include <Adafruit_NeoPixel.h>
#define _basePixel Adafruit_NeoPixel
#else
#include "NativePixel.h"
#define _basePixel NativePixel
#endif

