// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Activity.h"
#include "Controller.h"
extern pixel::Controller &Pixels;

namespace pixel
{
    template <typename GRID, typename PALETTE>
    class PixelActivity : public Activity
    {
    protected:
        GRID &grid;
        PALETTE &palette;
        uint16_t pulseWidth = 20;
        uint32_t next = 0;

    public:
        PixelActivity(GRID &grid,
                      PALETTE &palette,
                      uint16_t pulseWidth = 20)
            : grid(grid),
              palette(palette),
              pulseWidth(pulseWidth) {}

        // monitor overrides
        virtual void Reset() { next = 0; }
        virtual bool Ready()
        {
            auto now = Monitor::Now32();
            if (now >= next)
            {
                next = now + pulseWidth;
                return true;
            }
            return false;
        }
        virtual bool Done() { return false; }

        // timing
        inline uint16_t PulseWidth() const { return pulseWidth; }
        inline uint16_t PulseWidth(uint16_t v) { return pulseWidth = v; }

        virtual void Update()
        {
            grid.SpinValues(Pixels, grid, palette);
        }
    };

} // namespace pixel
