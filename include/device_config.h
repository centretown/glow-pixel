// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Device.h"
#include "Controller.h"

using pixel::Controller;
using pixel::Device;
using pixel::pixel_index;

#ifndef ARDUINO

const uint8_t device_count = 5;

const uint16_t device_01_size = 9;
const uint16_t device_02_size = 9;
const uint16_t device_03_size = 9;
const uint16_t device_04_size = 9;
const uint16_t device_05_size = 30;

const uint16_t pixel_count =
    device_01_size +
    device_02_size +
    device_03_size +
    device_04_size +
    device_05_size;

const uint16_t pixel_partitions[device_count + 1] =
    {
        0,
        device_01_size,
        device_01_size + device_02_size,
        device_01_size + device_02_size + device_03_size,
        device_01_size + device_02_size + device_03_size + device_04_size,
        device_01_size + device_02_size + device_03_size + device_04_size + device_05_size,
};

static NativeDevice driver_01(device_01_size);
static NativeDevice driver_02(device_02_size);
static NativeDevice driver_03(device_03_size);
static NativeDevice driver_04(device_04_size);
static NativeDevice driver_05(device_05_size);

static Device device_01(driver_01);
static Device device_02(driver_02);
static Device device_03(driver_03);
static Device device_04(driver_04);
static Device device_05(driver_05);

Device pixelDevices[] = {
    device_01,
    device_02,
    device_03,
    device_04,
    device_05,
};

#else // ARDUINO

#ifdef MEGAATMEGA2560
const uint8_t device_count = 2;

const uint16_t device_01_size = 19;
const uint16_t device_02_size = 15;

const uint16_t pixel_pin_01 = 7;
const uint16_t pixel_pin_02 = 6;

const uint16_t pixel_count =
    device_01_size + device_02_size;

const uint16_t pixel_partitions[device_count + 1] = {
    0,
    device_01_size,
    device_01_size + device_02_size,
};

static Adafruit_NeoPixel
    device_01(device_01_size, pixel_pin_01,
              NEO_BRG + NEO_KHZ800);
static Adafruit_NeoPixel
    device_02(device_02_size, pixel_pin_02,
              NEO_BRG + NEO_KHZ800);

Device pixel_device_01(device_01);
Device pixel_device_02(device_02);

Device pixelDevices[device_count] = {
    pixel_device_01,
    pixel_device_02,
};
// MEGAATMEGA2560
#endif
#ifdef ESP32
const uint8_t device_count = 5;

const uint16_t device_01_size = 9;
const uint16_t device_02_size = 9;
const uint16_t device_03_size = 9;
const uint16_t device_04_size = 9;
const uint16_t device_05_size = 30;

const uint16_t pixel_pin_01 = 13;
const uint16_t pixel_pin_02 = 27;
const uint16_t pixel_pin_03 = 14;
const uint16_t pixel_pin_04 = 12;
const uint16_t pixel_pin_05 = 26;

const uint16_t pixel_count =
    device_01_size +
    device_02_size +
    device_03_size +
    device_04_size +
    device_05_size;

const uint16_t pixel_partitions[device_count + 1] = {
    0,
    device_01_size,
    device_01_size + device_02_size,
    device_01_size + device_02_size + device_03_size,
    device_01_size + device_02_size + device_03_size + device_04_size,
    device_01_size + device_02_size + device_03_size + device_04_size + device_05_size,
};

static Adafruit_NeoPixel
    device_01(device_01_size, pixel_pin_01,
              NEO_GRB + NEO_KHZ800); // CH7
static Adafruit_NeoPixel
    device_02(device_02_size, pixel_pin_02,
              NEO_GRB + NEO_KHZ800); // CH6
static Adafruit_NeoPixel
    device_03(device_03_size, pixel_pin_03,
              NEO_GRB + NEO_KHZ800); // CH5
static Adafruit_NeoPixel
    device_04(device_04_size, pixel_pin_04,
              NEO_GRB + NEO_KHZ800); // CH4
static Adafruit_NeoPixel
    device_05(device_05_size, pixel_pin_05,
              NEO_BRG + NEO_KHZ800); // CH9

static Device pixel_device_01(device_01);
static Device pixel_device_02(device_02);
static Device pixel_device_03(device_03);
static Device pixel_device_04(device_04);
static Device pixel_device_05(device_05);

Device pixelDevices[device_count] = {
    pixel_device_01,
    pixel_device_02,
    pixel_device_03,
    pixel_device_04,
    pixel_device_05,
};
#endif // ESP32
#ifdef XIAO
const uint8_t device_count = 1;

const uint16_t device_01_size = 8;

const uint16_t pixel_pin_01 = 15;

const uint16_t pixel_count = device_01_size;

const uint16_t pixel_partitions[device_count + 1] = {
    0,
    device_01_size,
};

static Adafruit_NeoPixel
    device_01(device_01_size, pixel_pin_01,
              NEO_GRB + NEO_KHZ800); // CH3

static Device pixel_device_01(device_01);
Device pixelDevices[] = {
    pixel_device_01,
};
#endif // XIAO
#endif // defined(ARDUINO)
