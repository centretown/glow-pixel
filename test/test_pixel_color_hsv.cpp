// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED

#include <unity.h>

#include "config.h"
#include "Putter.h"
#include "PixelColorHSV.h"

using namespace strip;

void clearPixels();
void map_hue_color(uint16_t hue,
                   uint8_t &r,
                   uint8_t &g,
                   uint8_t &b);
uint16_t map_hue(uint16_t hue);
uint32_t apply_saturation_value(uint8_t sat, uint8_t val,
                                uint8_t r, uint8_t g, uint8_t b);

void testColorHsv()
{
    uint16_t tHue = 0;
    uint8_t tSaturation = 0;
    uint8_t tValue = 127;
    PixelColorHSV hsv(tHue, tSaturation, tValue);
    TEST_ASSERT_EQUAL(tHue, hsv.Hue());
    TEST_ASSERT_EQUAL(tSaturation, hsv.Saturation());
    TEST_ASSERT_EQUAL(tValue, hsv.Value());

    PixelColor colorHsv;
    colorHsv.Hue(tHue, tSaturation, tValue);

    color_pack pack = hsv.ToRGB();
    PixelColor color(pack);
    TEST_ASSERT_EQUAL_HEX32(0x808080, pack);

    tHue = 0;
    tSaturation = 127;
    tValue = 127;
    hsv.HSV(tHue, tSaturation, tValue);
    TEST_ASSERT_EQUAL(tHue, hsv.Hue());
    TEST_ASSERT_EQUAL(tSaturation, hsv.Saturation());
    TEST_ASSERT_EQUAL(tValue, hsv.Value());
    pack = hsv.ToRGB();
    color.Pack(pack);
    colorHsv.Hue(tHue, tSaturation, tValue);
    TEST_ASSERT_EQUAL_HEX32(colorHsv.Pack(), pack);
    TEST_ASSERT_EQUAL_HEX32(0x804040, pack);
}

void testHsvStepsOrg(uint16_t tHue, uint8_t tSaturation, uint8_t tValue)
{
    uint8_t red, green, blue;
    red = green = blue = 0;
    uint16_t mapped_hue_org = map_hue(tHue);
    map_hue_color(mapped_hue_org,
                  red,
                  green,
                  blue);
    uint32_t packed_org = apply_saturation_value(tSaturation, tValue,
                                                 red, green, blue);
    PixelColor colorHsv;
    colorHsv.Hue(tHue, tSaturation, tValue);
    TEST_ASSERT_EQUAL_HEX32(colorHsv.Pack(), packed_org);
}

void testHsvStepsNew(uint16_t tHue, uint8_t tSaturation, uint8_t tValue)
{
    uint8_t red, green, blue;
    red = green = blue = 0;
    uint16_t mapped_hue_org = map_hue(tHue);
    map_hue_color(mapped_hue_org,
                  red,
                  green,
                  blue);
    uint32_t packed_org = apply_saturation_value(tSaturation, tValue,
                                                 red, green, blue);

    PixelColorHSV hsv(tHue, tSaturation, tValue);
    TEST_ASSERT_EQUAL(tHue, hsv.Hue());
    TEST_ASSERT_EQUAL(tSaturation, hsv.Saturation());
    TEST_ASSERT_EQUAL(tValue, hsv.Value());

    uint16_t mapped_hue_new = hsv.mapHue();
    char buffer[32] = {0};
    snprintf(buffer, sizeof(buffer), "h=%x,s=%x,v=%x", tHue, tSaturation, tValue);
    TEST_ASSERT_EQUAL_HEX16_MESSAGE(mapped_hue_org, mapped_hue_new, buffer);

    color_pack pack = hsv.mapHueToColor(mapped_hue_new);
    PixelColor color(pack);

    TEST_ASSERT_EQUAL_HEX8(red, color.Red());
    TEST_ASSERT_EQUAL_HEX8(green, color.Green());
    TEST_ASSERT_EQUAL_HEX8(blue, color.Blue());

    pack = color.Pack();
    color_pack packed_new = hsv.applySaturationValue(pack);
    TEST_ASSERT_EQUAL_HEX32(packed_org, packed_new);
}

static uint16_t hueTable[]{
    0x0000, 0x0001, 0x0003, 0x0082, 0x00f0, 0x02f0, //
    0x0300, 0x0301, 0x0ff3, 0x0fff, 0xf0f0, 0xffff, //
};
static uint8_t hueCount = sizeof(hueTable) / sizeof(hueTable[0]);

static uint8_t satTable[]{
    0x00, 0x01, 0x03, 0x81, 0x83, 0x88, //
    0xdd, 0xde, 0xe1, 0xf0, 0xfc, 0xff, //
};
static uint8_t satCount = sizeof(satTable) / sizeof(satTable[0]);

static uint8_t valTable[]{
    0x00, 0x06, 0x15, 0x55, 0x73, 0x80, //
    0x8f, 0xa3, 0xc2, 0xd0, 0xec, 0xff, //
};
static uint8_t valCount = sizeof(valTable) / sizeof(valTable[0]);

void testHsvSteps()
{
    for (uint8_t i = 0; i < hueCount; i++)
    {
        uint16_t tHue = hueTable[i];
        uint8_t tSaturation = 0;
        uint8_t tValue = 0;

        for (uint8_t j = 0; j < satCount; j++)
        {
            tSaturation = satTable[j];
            testHsvStepsOrg(tHue, tSaturation, tValue);
            testHsvStepsNew(tHue, tSaturation, tValue);
            for (uint8_t k = 0; k < valCount; k++)
            {
                tValue = valTable[k];
                testHsvStepsOrg(tHue, tSaturation, tValue);
                testHsvStepsNew(tHue, tSaturation, tValue);
            }
        }

        for (uint8_t k = 0; k < valCount; k++)
        {
            tValue = valTable[k];
            testHsvStepsOrg(tHue, tSaturation, tValue);
            testHsvStepsNew(tHue, tSaturation, tValue);
            for (uint8_t j = 0; j < satCount; j++)
            {
                tSaturation = satTable[j];
                testHsvStepsOrg(tHue, tSaturation, tValue);
                testHsvStepsNew(tHue, tSaturation, tValue);
            }
        }
    }
}

void testHsvSingleStep()
{
    uint16_t tHue = 0;
    uint8_t tSaturation = 127;
    uint8_t tValue = 127;

    testHsvStepsOrg(tHue, tSaturation, tValue);
    testHsvStepsNew(tHue, tSaturation, tValue);
}

void testPixelColorHsv()
{
    RUN_TEST(testHsvSingleStep);
    RUN_TEST(testHsvSteps);
    // RUN_TEST(testColorHsv);
}
