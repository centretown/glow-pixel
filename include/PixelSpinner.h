// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "config.h"

namespace pixel
{
    class PixelSpinner
    {
    private:
        Controller &pixels;
        Range range;

    public:
        PixelSpinner() : pixels(Pixels) {}

        void SpinDevice(uint16_t index, color_pack color)
        {
            Device &device = pixels.device(index);
            device.Spin(device, color);
            device.Update();
        }

        void SpinDevices(color_pack color)
        {
            for (uint8_t i = 0; i < pixels.device_count(); i++)
            {
                SpinDevice(i, color);
            }
        }
    };
} // namespace pixel
