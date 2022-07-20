// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED

#include <unity.h>
#include "base.h"
#include "Benchmark.h"
#include "wait.h"
#include <ArduinoJson.h>

using glow::Benchmark;

void testBenchMarkPrint()
{
    Benchmark benchmark;
    set_real_time(true);

    benchmark.Begin("testBenchMarkPrint");
    wait(1000);
    benchmark.End();

    set_real_time(false);
}

void testBenchMark()
{
    RUN_TEST(testBenchMarkPrint);
}
