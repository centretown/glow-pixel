// Copyright (c) 2022 Dave Marsh. See LICENSE.
#ifndef PIO_UNIT_TESTING
#include <base.h>
#include <BlinkActivity.h>

BlinkSettings blinkSettings;
BlinkActivity blink(blinkSettings);

#ifdef ARDUINO
void setup()
{
    blinkSettings.On(100);
    blinkSettings.Off(2000);
    blink.Setup();
}

uint64_t now;
void loop()
{
    Activity::Cycle();
    blink.Pulse();
}
#else
int main(int argc, char **argv)
{
    blink.Setup();
    for (auto i = 0; i < 1000; i++)
    {
        Activity::Cycle();
        blink.Pulse();
    }
}
#endif
#endif