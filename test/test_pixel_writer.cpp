// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED

#include <unity.h>
#include "base.h"
#include "config.h"

void wait(uint32_t ms = 1000)
{
#ifdef ARDUINO
    delay(ms);
#endif
}

void testColor(uint32_t color)
{
    size_t count = writer.Length();
    for (size_t i = 0; i < count; i++)
    {
        writer.Put(i, color);
    }
    writer.Update();
    wait();
}

void testPixelWriter()
{
    writer.Setup();

    uint32_t color = writer.Color(0xff, 0, 0);
    testColor(color);
    wait();

    color = writer.Color(0, 0xff, 0);
    testColor(color);
    wait();

    color = writer.Color(0, 0, 0xff);
    testColor(color);
    wait();

    color = writer.Color(0, 0x80, 0x80);
    testColor(color);
    wait();

    color = writer.Color(0, 0, 0);
    testColor(color);
}

void testPixelWriters()
{
    RUN_TEST(testPixelWriter);
}
