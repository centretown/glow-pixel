// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "Monitor.h"
#include "PixelStrip.h"

using glow::Monitor;

namespace strip
{
    class PixelMonitor : public Monitor
    {
    private:
        bool ready = true;

    protected:
        PixelStrip *pixel;

    public:
        PixelMonitor(PixelStrip *pixel) : pixel(pixel) {}
        ~PixelMonitor() {}

        virtual void Reset() {}
        virtual bool Ready();
        virtual bool Done() { return false; };
    };
}