#define UNITY_INCLUDE_PRINT_FORMATTED

#include <unity.h>
#include "wait.h"

#include "Color.h"
#include "Range.h"

using color::Color;
using glow::Range;

#include "config.h"
pixel::Controller &Pixels = pixelController;

void testBuildController()
{
    TEST_ASSERT_GREATER_THAN(0, device_count);
    TEST_ASSERT_GREATER_THAN(0, pixel_count);
    TEST_ASSERT_EQUAL(pixel_count,
                      sizeof(theIndex) / sizeof(theIndex[0]));
    TEST_ASSERT_EQUAL(device_count + 1,
                      sizeof(pixel_partitions) / sizeof(pixel_partitions[0]));
    TEST_ASSERT_EQUAL(device_count,
                      sizeof(pixelDevices) / sizeof(pixelDevices[0]));

    buildIndex();
    uint8_t deviceIndex = 0;
    for (uint16_t i = 0; i < pixel_count; i++)
    {
        for (deviceIndex = 0;
             pixel_partitions[deviceIndex + 1] <= i;
             deviceIndex++)
            ;
        TEST_ASSERT_EQUAL(deviceIndex, theIndex[i].device);
        uint16_t offset = i - pixel_partitions[deviceIndex];
        TEST_ASSERT_EQUAL(offset, theIndex[i].offset);
    }

    pixelController.Setup(pixel_count, (pixel_index *)theIndex,
                          (Device *)pixelDevices, device_count);

    TEST_ASSERT_EQUAL(pixel_count,
                      pixelController.PixelCount());
    TEST_ASSERT_EQUAL(device_count,
                      pixelController.device_count());

    Color color(24, 0, 24);
    Range(0, pixel_count).Spin(pixelController, color.Pack());
    wait(1000);

    color.RGB(0, 24, 24);
    Range(pixelController.Scope()).Spin(pixelController, color.Pack());
    wait(1000);
}

void testBuildControllers()
{
    RUN_TEST(testBuildController);
}