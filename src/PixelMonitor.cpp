// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "PixelMonitor.h"
namespace pixel
{
    bool PixelMonitor::Ready()
    {
        bool r = ready;
        ready = false;
        return r;
    }
}