// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "ColorFilter.h"
#include "Range.h"
#include "Updater.h"
#include "config.h"

namespace glow
{
    class PixelUpdater : public Updater
    {
    public:
        virtual void Put(Range *range, PixelColor color, ColorFilter *filter)
        {
        }

        inline void Update()
        {
            Pixels.Update();
        }
    };

}