// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"
#include "PixelDevice.h"
#include "PixelController.h"

#ifdef ARDUINO
#include "NeoPixelDevice.h"
#else
#include "NativePixelDevice.h"
#endif

namespace glow
{
    extern PixelDevice *pixelDevices[];
    extern PixelController &Pixels;
    extern size_t PixelDeviceCount();
}
