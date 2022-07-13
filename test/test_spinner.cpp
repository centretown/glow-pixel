#define UNITY_INCLUDE_PRINT_FORMATTED

#include <unity.h>
#include "base.h"
#include "config.h"
#include "PixelSpinner.h"
#include "wait.h"

using namespace pixel;

void testDevicesSpin()
{
    Color color(15, 0, 15);
    Color color1(0, 15, 15);
    Color color2(15, 15, 0);
    PixelSpinner spinner;
    spinner.SpinDevices(color.Pack());
    wait(1000);
    spinner.SpinDevices(color1.Pack());
    wait(1000);
    spinner.SpinDevices(color2.Pack());
}

void testPixelSpinner()
{
    RUN_TEST(testDevicesSpin);
}