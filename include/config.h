// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Device.h"
#include "Controller.h"

using pixel::Controller;
using pixel::Device;
using pixel::pixel_index;

#include "device_config.h"
// NOW DEFINED:
// const uint8_t device_count;
// uint16_t pixel_count;
// Device pixelDevices[]
// uint16_t pixel_partitions[device_count + 1]

static Controller pixelController;

pixel_index theIndex[pixel_count];

void buildIndex()
{
    for (uint16_t i = 0; i < pixel_count; i++)
    {
        uint8_t deviceIndex = 0;
        for (; pixel_partitions[deviceIndex + 1] <= i;
             deviceIndex++)
            ;
        theIndex[i].offset = i - pixel_partitions[deviceIndex];
        theIndex[i].device = deviceIndex;
    }
}

Controller &BuildController()
{
    buildIndex();
    pixelController.Setup(pixel_count, (pixel_index *)theIndex,
                          (Device *)pixelDevices, device_count);
    return pixelController;
}
