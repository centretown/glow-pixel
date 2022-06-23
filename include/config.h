// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"
#include "PixelWriter.h"

namespace glow
{
    extern PixelWriter *pixelWriters[];
    extern size_t pixelWritersCount;
}

#ifdef ARDUINO
#include "NeoPixelWriter.h"
#else
#include "NativePixelWriter.h"
#endif
