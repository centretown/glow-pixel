// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "MonitoredActivity.h"
#include "PixelMonitor.h"

namespace glow
{
    class PixelActivity : public MonitoredActivity
    {
    private:
        PixelStrip *pixel;

    public:
        PixelActivity(PixelMonitor *monitor, PixelStrip *pixel)
            : MonitoredActivity(monitor), pixel(pixel) {}
        ~PixelActivity() {}

        virtual void Update()
        {
            pixel->Update();
        }
    };
}