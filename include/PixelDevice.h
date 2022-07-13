// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Color.h"
#include "Range.h"

using glow::Range;

namespace pixel
{
    template <typename DEVICE>
    class DeviceGenerator : public Range
    {
    private:
        DEVICE &device;
        const uint16_t pixelCount;
        Color color;

    public:
        DeviceGenerator(DEVICE &device)
            : Range(0, device.numPixels()), device(device),
              pixelCount(device.numPixels()) {}

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
    class Device : public DeviceGenerator<Adafruit_NeoPixel>
    {
    public:
        Device(Adafruit_NeoPixel &device)
            : DeviceGenerator<Adafruit_NeoPixel>(device) {}
    };
#else
#include "NativeDevice.h"
    class Device : public DeviceGenerator<NativeDevice>
    {
    public:
        Device(NativeDevice &device)
            : DeviceGenerator<NativeDevice>(device) {}
    };
#endif

}