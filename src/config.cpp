// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "config.h"

namespace strip
{
#ifdef ARDUINO
#ifdef MEGAATMEGA2560
    const uint16_t device_01_size = 19;
    const uint16_t device_02_size = 15;

    const uint16_t pixel_pin_01 = 7;
    const uint16_t pixel_pin_02 = 6;

    const uint8_t device_count = 2;

    const uint16_t pixel_count =
        device_01_size +
        device_02_size;

    const uint16_t pixel_partitions[device_count + 1] = {
        0,
        device_01_size,
        device_01_size + device_02_size,
    };

    static Adafruit_NeoPixel device_01(device_01_size, pixel_pin_01,
                                       NEO_BRG + NEO_KHZ800);
    static Adafruit_NeoPixel device_02(device_02_size, pixel_pin_02,
                                       NEO_BRG + NEO_KHZ800);

    static NeoPixelDevice pixel_device_01(device_01);
    static NeoPixelDevice pixel_device_02(device_02);

    PixelDevice *pixelDevices[] = {
        &pixel_device_01,
        &pixel_device_02,
    };
    // MEGAATMEGA2560
#else

#ifdef ESP32
#ifndef ESP32LOCAL
    const uint16_t device_01_size = 9;
    const uint16_t device_02_size = 9;
    const uint16_t device_03_size = 9;
    const uint16_t device_04_size = 9;
    const uint16_t device_05_size = 4;

    const uint16_t pixel_pin_01 = 13; 
    const uint16_t pixel_pin_02 = 27;
    const uint16_t pixel_pin_03 = 14;
    const uint16_t pixel_pin_04 = 12;
    const uint16_t pixel_pin_05 = 26;

    const uint8_t device_count = 5;

    const uint16_t pixel_count =
        device_01_size +
        device_02_size +
        device_03_size +
        device_04_size +
        device_05_size;

    const uint16_t pixel_partitions[device_count + 1] = {
        0,
        device_01_size,
        device_01_size + device_02_size,
        device_01_size + device_02_size + device_03_size,
        device_01_size + device_02_size + device_03_size + device_04_size,
        device_01_size + device_02_size + device_03_size + device_04_size + device_05_size,
    };

    static Adafruit_NeoPixel device_01(device_01_size, pixel_pin_01,
                                       NEO_GRB + NEO_KHZ800); // CH7
    static Adafruit_NeoPixel device_02(device_02_size, pixel_pin_02,
                                       NEO_GRB + NEO_KHZ800); // CH6
    static Adafruit_NeoPixel device_03(device_03_size, pixel_pin_03,
                                       NEO_GRB + NEO_KHZ800); // CH5
    static Adafruit_NeoPixel device_04(device_04_size, pixel_pin_04,
                                       NEO_GRB + NEO_KHZ800); // CH4
    static Adafruit_NeoPixel device_05(device_05_size, pixel_pin_05,
                                       NEO_GRB + NEO_KHZ800); // CH9

    static NeoPixelDevice pixel_device_01(device_01);
    static NeoPixelDevice pixel_device_02(device_02);
    static NeoPixelDevice pixel_device_03(device_03);
    static NeoPixelDevice pixel_device_04(device_04);
    static NeoPixelDevice pixel_device_05(device_05);

    PixelDevice *pixelDevices[] = {
        &pixel_device_01,
        &pixel_device_02,
        &pixel_device_03,
        &pixel_device_04,
        &pixel_device_05,
    };
    // ESP32
#else  // ESP32LOCAL
    const uint16_t device_01_size = 8;

    const uint16_t pixel_pin_01 = 15;

    const uint8_t device_count = 1;

    const uint16_t pixel_count = device_01_size;

    const uint16_t pixel_partitions[device_count + 1] = {
        0,
        device_01_size,
    };

    static Adafruit_NeoPixel device_01(device_01_size, pixel_pin_01,
                                       NEO_GRB + NEO_KHZ800); // CH3

    static NeoPixelDevice pixel_device_01(device_01);
    PixelDevice *pixelDevices[] = {
        &pixel_device_01,
    };
    // ESP32LOCAL
#endif // not ESP32LOCAL
#else  // XIAO
    const uint16_t device_01_size = 8;

    const uint16_t pixel_pin_01 = 15;

    const uint8_t device_count = 1;

    const uint16_t pixel_count = device_01_size;

    const uint16_t pixel_partitions[device_count + 1] = {
        0,
        device_01_size,
    };

    static Adafruit_NeoPixel device_01(device_01_size, pixel_pin_01,
                                       NEO_GRB + NEO_KHZ800); // CH3

    static NeoPixelDevice pixel_device_01(device_01);
    PixelDevice *pixelDevices[] = {
        &pixel_device_01,
    };
    // XIAO
#endif // ESP32

#endif // MEGAATMEGA2560

#else  // NATIVE
    const uint16_t device_01_size = 9;
    const uint16_t device_02_size = 9;
    const uint16_t device_03_size = 9;
    const uint16_t device_04_size = 9;
    const uint16_t device_05_size = 4;

    const uint8_t device_count = 5;

    const uint16_t pixel_count =
        device_01_size +
        device_02_size +
        device_03_size +
        device_04_size +
        device_05_size;

    const uint16_t pixel_partitions[device_count + 1] =
        {
            0,
            device_01_size,
            device_01_size + device_02_size,
            device_01_size + device_02_size + device_03_size,
            device_01_size + device_02_size + device_03_size + device_04_size,
            device_01_size + device_02_size + device_03_size + device_04_size + device_05_size,
    };

    static NativePixelDevice pixel_device_01(device_01_size);
    static NativePixelDevice pixel_device_02(device_02_size);
    static NativePixelDevice pixel_device_03(device_03_size);
    static NativePixelDevice pixel_device_04(device_04_size);
    static NativePixelDevice pixel_device_05(device_05_size);

    PixelDevice *pixelDevices[] = {
        &pixel_device_01,
        &pixel_device_02,
        &pixel_device_03,
        &pixel_device_04,
        &pixel_device_05,
    };
#endif // ARDUINO
    pixel_index theIndex[pixel_count];
    const pixel_index *pixelIndex = buildIndex(theIndex, pixel_count, pixel_partitions);

    static PixelController pixelController(pixelDevices, device_count);
    PixelController &Pixels = pixelController;

    pixel_index *buildIndex(pixel_index *index,
                            const uint16_t pixelCount,
                            const uint16_t *partitions)
    {
        for (size_t i = 0; i < pixelCount; i++)
        {
            uint8_t deviceIndex = 0;
            for (; partitions[deviceIndex + 1] <= i;
                 deviceIndex++)
                ;
            index[i].offset = i - partitions[deviceIndex];
            index[i].device = deviceIndex;
        }
        return index;
    }

} // namespace strip
