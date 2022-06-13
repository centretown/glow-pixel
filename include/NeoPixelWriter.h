// Copyright (c) 2022 Dave Marsh. See LICENSE.

#ifdef ARDUINO
#pragma once

#include "PixelWriter.h"
#include <Adafruit_NeoPixel.h>

class NeoPixelWriter : public PixelWriter
{
private:
    Adafruit_NeoPixel &device;

public:
    NeoPixelWriter(Adafruit_NeoPixel &device) : device(device)
    {
        length = device.numPixels();
    }
    ~NeoPixelWriter() {}

    virtual void Setup()
    {
        device.begin();
        device.clear();
        device.show();
    }

    virtual void Put(uint16_t index, uint8_t red, uint8_t green, uint8_t blue)
    {
        device.setPixelColor(index, red, green, blue);
    }

    virtual void Update()
    {
        device.show();
    }
};
#endif