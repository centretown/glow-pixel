// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "PixelController.h"

namespace glow
{
    // PixelController controller(pixelWriters, pixelWritersCount);

    PixelController::PixelController(PixelDevice **devices, uint16_t deviceCount)
        : devices(devices), deviceCount(deviceCount)
    {
        if (deviceCount > MAX_PIXEL_DEVICES)
        {
            deviceCount = MAX_PIXEL_DEVICES;
        }

        for (uint16_t i = 0; i < deviceCount; i++)
        {
            pixelCount += devices[i]->PixelCount();
            partitions[i] = pixelCount;
        }
    }

    void PixelController::Setup()
    {
        for (uint16_t i = 0; i < deviceCount; i++)
        {
            devices[i]->Setup();
        }
    }

    void PixelController::Put(uint16_t index, PixelColor &color)
    {
        index %= pixelCount;
        uint16_t writerIndex = findWriterIndex(index);
        if (writerIndex > 0)
        {
            index -= partitions[writerIndex - 1];
        }
        devices[writerIndex]->Put(index, color);
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
