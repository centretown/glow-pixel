// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "PixelController.h"

namespace strip
{

    void PixelController::Setup()
    {
        for (uint8_t i = 0; i < deviceCount; i++)
        {
            devices[i]->Setup();
        }
    }

    void PixelController::SweepColor(PixelMapper *mapper, color_pack color, bool reverse)
    {
        ColorSweep colorSweep(mapper, color);
        Sweep(mapper->Pack(), colorSweep);
    }

    void PixelController::Update()
    {
        for (uint16_t i = 0; i < deviceCount; i++)
        {
            if (mustUpdate(i))
            {
                devices[i]->Update();
            }
        }
        updateDone();
    }
}
