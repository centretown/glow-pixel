// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "PixelColor.h"

namespace strip
{
    template <typename DEVICE>
    class PixelDeviceGenerator
    {
    private:
        DEVICE &device;
        const uint16_t pixelCount;
        PixelColor color;

    public:
        PixelDeviceGenerator(DEVICE &device)
            : device(device), pixelCount(device.numPixels()) {}

        inline const uint16_t PixelCount() { return pixelCount; }

        inline void Setup()
        {
            device.begin();
            device.clear();
            device.show();
        }

        inline void Put(uint16_t index, color_pack pack)
        {
            color.Pack(pack);
            device.setPixelColor(index, color.Red(),
                                 color.Green(), color.Blue());
        }

        inline void Update()
        {
            device.show();
        }
    };

#ifdef ARDUINO
#include <Adafruit_NeoPixel.h>
    class PixelDevice : public PixelDeviceGenerator<Adafruit_NeoPixel>
    {
    public:
        PixelDevice(Adafruit_NeoPixel &device)
            : PixelDeviceGenerator<Adafruit_NeoPixel>(device) {}
    };
#else
#include "NativeDevice.h"
    class PixelDevice : public PixelDeviceGenerator<NativeDevice>
    {
    public:
        PixelDevice(NativeDevice &device)
            : PixelDeviceGenerator<NativeDevice>(device) {}
    };
#endif

}