// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "PixelController.h"
#include "ColorFilter.h"
#include "PixelMapper.h"
#include "config.h"

namespace strip
{
    class PixelStrip
    {
    public:
        // inline void Put(uint16_t index, PixelColor color, PixelMapper *m = NULL)
        // {
        //     if (m == NULL)
        //     {
        //         m = mapper;
        //     }
        //     Pixels.Put(m->Get(index), color);
        // }

        // inline void Put(uint16_t index, PixelColor color, ColorFilter *filter)
        // {
        //     PixelColor filtered;
        //     filter->Apply(color, filtered);
        //     Pixels.Put(mapper->Get(index), filtered);
        // }

        // inline void Update()
        // {
        //     Pixels.Update();
        // }
    };
}