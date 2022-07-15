// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "Monitor.h"

using glow::Monitor;

namespace pixel
{
    class PixelMonitor : public Monitor
    {
    private:
        bool ready = true;

    protected:
    public:
        PixelMonitor() {}
        ~PixelMonitor() {}

        virtual void Reset() {}
        virtual bool Ready();
        virtual bool Done() { return false; };
    };
}