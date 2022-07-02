// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED

#include <unity.h>

#include "PixelController.h"
#include "config.h"
#include "PixelFrame.h"
#include "Putter.h"

using namespace strip;

void clearPixels();

void putFrame(PixelFrame *frame, PixelColor color, uint32_t ms = 100)
{
    TEST_ASSERT(frame);
    PixelColor backGround(15, 15, 5);
    Pixels.SweepColor(frame, backGround);
    Pixels.Update();

    Puttee puttee;
    puttee.mapper = frame;
    puttee.color = color;
    puttee.ms = ms;
    Putter putter;

    putter.Sweep(frame, &puttee);

    wait(1000);
    clearPixels();
}

void testIndicatorFrame()
{
    PixelColor color;
    PixelFrame indicator(Pixels.Scope(), 1);
    indicator.Begin(indicator.End() - 4);
    indicator.Resize();
    TEST_ASSERT_EQUAL(Pixels.Scope()->End() - 4, indicator.Begin());
    TEST_ASSERT_EQUAL(Pixels.Scope()->End(), indicator.End());
    TEST_ASSERT_EQUAL(1, indicator.Rows());
    TEST_ASSERT_EQUAL(4, indicator.Cols());

    color.GBR(255, 255);
    putFrame(&indicator, color);

    indicator.Begin(indicator.End() - 5);
    indicator.Resize();
    TEST_ASSERT_EQUAL(1, indicator.Rows());
    TEST_ASSERT_EQUAL(5, indicator.Cols());

    color.BGR(255, 255);
    putFrame(&indicator, color);
}

void testPixelFrame()
{
    PixelColor color(255, 0, 255);

    PixelFrame frame(Pixels.Scope(), 4);
    TEST_ASSERT_EQUAL(Pixels.Scope()->Begin(), frame.Begin());
    TEST_ASSERT_EQUAL(Pixels.Scope()->End(), frame.End());
    frame.End(frame.End() - 4);
    frame.Resize();
    // TEST_ASSERT_EQUAL(9, frame.Cols());
    putFrame(&frame, color);

    frame.Reverse(true);
    TEST_ASSERT(frame.Reverse());
    color.BGR(127, 127);
    putFrame(&frame, color);
}

void testPixelFrames()
{
    RUN_TEST(testIndicatorFrame);
    RUN_TEST(testPixelFrame);
}