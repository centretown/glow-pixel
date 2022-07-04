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
    SimpleRange rows(0, 1);
    SimpleRange cols(0, 4);
    auto end = Pixels.Scope()->End();
    PixelFrame indicator(end - 4, end, 4, &rows, &cols);
    auto begin = indicator.Begin();

    indicator.Orient(AS_ROWS);
    TEST_ASSERT_EQUAL(end - 4, indicator.Begin());
    TEST_ASSERT_EQUAL(end, indicator.End());
    TEST_ASSERT_EQUAL(end - 4, indicator.Get(begin));
    TEST_ASSERT_EQUAL(begin, indicator.Get(begin));
    TEST_ASSERT_EQUAL(begin + 1, indicator.Get(begin + 1));
    TEST_ASSERT_EQUAL(begin + 2, indicator.Get(begin + 2));
    TEST_ASSERT_EQUAL(begin + 3, indicator.Get(begin + 3));

    color.GBR(127, 127);
    indicator.Orient(AS_RANGE);
    putFrame(&indicator, color);

    color.RGB(127, 127);
    indicator.Orient(AS_ROWS);
    putFrame(&indicator, color);

    cols.Resize(0, 5);
    indicator.Resize(end - 5, end, 5, &rows, &cols);
    begin = indicator.Begin();
    TEST_ASSERT_EQUAL(5, indicator.Length());
    TEST_ASSERT_EQUAL(end - 5, indicator.Get(begin));
    TEST_ASSERT_EQUAL(begin, indicator.Get(begin));
    TEST_ASSERT_EQUAL(begin + 1, indicator.Get(begin + 1));
    TEST_ASSERT_EQUAL(begin + 2, indicator.Get(begin + 2));
    TEST_ASSERT_EQUAL(begin + 3, indicator.Get(begin + 3));

    color.BGR(127, 127);
    indicator.Orient(AS_ROWS);
    putFrame(&indicator, color);

    color.BGR(127, 0, 127);
    indicator.Orient(AS_ROWS);
    indicator.Reverse(true);
    putFrame(&indicator, color);
}

void testPixelGrid()
{
    // PixelColor color(127, 0, 127);

    // PixelFrame frame(4);
    // TEST_ASSERT_EQUAL(Pixels.Scope()->Begin(), frame.Begin());
    // TEST_ASSERT_EQUAL(Pixels.Scope()->End(), frame.End());
    // frame.End(frame.End() - 4);
    // frame.Resize();
    // // TEST_ASSERT_EQUAL(9, frame.Cols());
    // putFrame(&frame, color);

    // frame.Reverse(true);
    // TEST_ASSERT(frame.Reverse());
    // color.BGR(127, 127);
    // putFrame(&frame, color);

    // frame.Reverse(false);
    // putFrame(&frame, color);

    // frame.End(frame.End() - 2);
    // frame.Resize();
    // putFrame(&frame, color);
}

void testPixelFrames()
{
    RUN_TEST(testIndicatorFrame);
    RUN_TEST(testPixelGrid);
}