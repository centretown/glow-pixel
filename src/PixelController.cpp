// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "PixelController.h"

namespace strip
{

    PixelController::PixelController(PixelDevice **devices, uint8_t deviceCount)
        : devices(devices), deviceCount(deviceCount)
    {
        if (deviceCount > MAX_PIXEL_DEVICES)
        {
            deviceCount = MAX_PIXEL_DEVICES;
        }

        partitions[0] = 0;
        for (uint16_t i = 0; i < deviceCount; i++)
        {
            pixelCount += devices[i]->PixelCount();
            partitions[i + 1] = pixelCount;
        }
        range.Resize(0, pixelCount);
    }

    void PixelController::Setup()
    {
        for (uint8_t i = 0; i < deviceCount; i++)
        {
            devices[i]->Setup();
        }
    }

    void PixelController::SweepColor(PixelMapper *mapper, color_pack packed)
    {
        ColorSweep sw(mapper, packed);
        Sweep(mapper, &sw);
    }

    void PixelController::Put(uint16_t index, color_pack packed)
    {
        select(index);
        selectedDevice->Put(selectedOffset, packed);
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
