// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED

#include <unity.h>
#include "base.h"
#include "config.h"
#include "PixelWriter.h"
using namespace glow;

void wait(uint32_t ms = 500)
{
#ifdef ARDUINO
    delay(ms);
#endif
}

void testColor(PixelWriter *writer, PixelColor &color)
{
    size_t count = writer->Length();
    for (size_t i = 0; i < count; i++)
    {
        writer->Put(i, color);
    }
    writer->Update();
    wait();
}

void testPixelWriter()
{
    for (size_t i = 0; i < pixelWritersCount; i++)
    {
        pixelWriters[i]->Setup();
    }

    PixelWriter *writer;
    PixelColor color;
    for (size_t i = 0; i < pixelWritersCount; i++)
    {
        writer = pixelWriters[i];
        color.RGB(0xff, 0, 0);
        testColor(writer, color);
        color.RGB(0, 0xff, 0);
        testColor(writer, color);
        color.RGB(0, 0, 0xff);
        testColor(writer, color);
        color.RGB();
        testColor(writer, color);
    }
}

void testPixelWriters()
{
    RUN_TEST(testPixelWriter);
}
