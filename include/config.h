// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"
#include "PixelWriter.h"
#include "PixelController.h"

#ifdef ARDUINO
#include "NeoPixelWriter.h"
#else
#include "NativePixelWriter.h"
#endif

namespace glow
{
    extern PixelWriter *pixelWriters[];
    extern size_t pixelWritersCount;
    extern PixelController pixelController;
}
