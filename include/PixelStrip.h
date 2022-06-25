// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "PixelController.h"
#include "ColorFilter.h"
#include "PixelMapper.h"
#include "config.h"

namespace glow
{
    class PixelStrip
    {
    private:
        PixelMapper *mapper;

    public:
        PixelStrip(PixelMapper *mapper) : mapper(mapper) {}

        inline uint16_t Length() { return mapper->Length(); }

        inline void Put(uint16_t index, PixelColor color)
        {
            pixelController.Put(mapper->Get(index), color);
        }

        inline void Put(uint16_t index, PixelColor color, ColorFilter *filter)
        {
            PixelColor filtered;
            filter->Apply(color, filtered);
            pixelController.Put(mapper->Get(index), filtered);
        }

        inline void Update()
        {
            pixelController.Update();
        }
    };
}