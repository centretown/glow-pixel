// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED

#include <unity.h>
#include "base.h"
#include "config.h"
#include "PixelWriter.h"

void wait(uint32_t ms = 500)
{
#ifdef ARDUINO
    delay(ms);
#endif
}

void testColor(PixelWriter *writer, uint8_t red, uint8_t green, uint8_t blue)
{
    size_t count = writer->Length();
    for (size_t i = 0; i < count; i++)
    {
        writer->Put(i, red, green, blue);
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
    for (size_t i = 0; i < pixelWritersCount; i++)
    {
        writer = pixelWriters[i];
        testColor(writer, 0xff, 0, 0);
        testColor(writer, 0, 0xff, 0);
        testColor(writer, 0, 0, 0xff);
        testColor(writer, 0x80, 0x20, 0x80);
        testColor(writer, 0, 0, 0);
    }
}

void testPixelWriters()
{
    RUN_TEST(testPixelWriter);
}
