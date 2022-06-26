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
    extern size_t pixelDeviceCount;
    extern PixelController pixelController;
}
