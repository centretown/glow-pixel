// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "MonitoredActivity.h"
#include "PixelMonitor.h"

namespace glow
{
    class PixelActivity : public MonitoredActivity
    {
    private:
        PixelSettings *pixel;

    public:
        PixelActivity(PixelMonitor *monitor, PixelSettings *pixel)
            : MonitoredActivity(monitor), pixel(pixel) {}
        ~PixelActivity() {}

        virtual void Update()
        {
            pixel->Update();
        }
    };
}
