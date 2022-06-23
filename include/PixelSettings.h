// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "PixelController.h"
#include "PixelDimmer.h"

namespace glow
{
    class PixelSettings
    {
    protected:
        static PixelController control;

    protected:
        PixelColor color;
        PixelColor result;
        PixelDimmer dimmer;

    public:
        PixelSettings() {}

        inline PixelColor &Color() { return color; }
        inline PixelDimmer &Dimmer() { return dimmer; }

        virtual uint16_t Count() { return control.Count(); }
        virtual void Put(uint16_t index)
        {
            control.Put(index, dimmer.Filter(color, result));
        }

        virtual void Update()
        {
            control.Update(0, control.Count());
        }
    };
}