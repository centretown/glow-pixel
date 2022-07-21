// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Device.h"
#include "Color.h"

using glow::Range;
using glow::range_pack;

using color::Color;
using color::color_pack;

#ifdef ARDUINO
#include <Adafruit_NeoPixel.h>
#else
#include "NativeDevice.h"
#endif

namespace pixel
{
    template <typename DRIVER>
    class PixelController : Range // private range
    {
    private:
        uint16_t pixelCount = 0;
        pixel_index *pixelIndex = NULL;
        Device *devices = NULL;
        uint8_t deviceCount = 0;

    private:
        uint16_t selectedFlag = 0;

    public:
        PixelController() {}

        // Controller(Device *devices, const uint8_t deviceCount,
        //            pixel_index *pixelIndex, const uint16_t pixelCount)
        //     : Range(0, pixelCount),
        //       devices(devices), deviceCount(deviceCount),
        //       pixelIndex(pixelIndex), pixelCount(pixelCount)
        // {
        // }
        ~PixelController() {}

        inline uint16_t PixelCount() const { return pixelCount; }
        inline range_pack Scope() const { return Pack(); }

        void Setup(uint16_t pixel_count,
                   pixel_index *pixel_index,
                   Device *pixelDevices,
                   uint16_t device_count)
        {
            Resize(0, pixel_count);
            pixelCount = pixel_count;
            pixelIndex = pixel_index;
            devices = pixelDevices;
            deviceCount = device_count;
            for (uint8_t i = 0; i < deviceCount; i++)
            {
                devices[i].Setup();
            }
        }

        Device &device(uint8_t i)
        {
            return devices[i];
        }

        inline uint8_t device_count() { return deviceCount; }

        inline void Put(uint16_t index, color_pack color)
        {
            if (index < pixelCount)
            {
                pixel_index px = pixelIndex[index];
                devices[px.device].Put(px.offset, color);
                selectedFlag |= 1 << px.device;
            }
        }

        inline void Update()
        {
            for (uint16_t i = 0; i < deviceCount; i++)
            {
                if (mustUpdate(i))
                {
                    devices[i].Update();
                }
            }
            updateDone();
        }

    private:
        inline bool mustUpdate(size_t deviceIndex) const
        {
            return ((1 << deviceIndex) & selectedFlag);
        }

        inline void updateDone() { selectedFlag = 0; }
    };

#ifdef ARDUINO
    typedef PixelController<Adafruit_NeoPixel> Controller;
#else
    typedef PixelController<NativeDevice> Controller;
#endif

}
