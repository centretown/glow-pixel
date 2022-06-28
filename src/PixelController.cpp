// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "PixelController.h"

namespace glow
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
        range.Begin(0);
        range.End(pixelCount);
    }

    void PixelController::Setup()
    {
        for (uint8_t i = 0; i < deviceCount; i++)
        {
            devices[i]->Setup();
        }
    }

    void PixelController::Put(Range *range, PixelColor &color)
    {
        for (uint16_t index = range->Begin();
             index < range->End();
             index = range->Next(index))
        {
            select(index);
            selectedDevice->Put(selectedOffset, color);
        }
    }

    void PixelController::Put(uint16_t index, PixelColor &color)
    {
        index %= pixelCount;
        select(index);
        selectedDevice->Put(selectedOffset, color);
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
