// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "Monitor.h"
#include "PixelSettings.h"

namespace glow
{
    class PixelMonitor : public Monitor
    {
    private:
        bool ready = true;

    protected:
        PixelSettings *pixel;

    public:
        PixelMonitor(PixelSettings *pixel) : pixel(pixel) {}
        ~PixelMonitor() {}

        virtual void Reset() {}
        virtual bool Ready();
        virtual bool Done() { return false; };
    };
}