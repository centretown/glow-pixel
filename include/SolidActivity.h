// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"
#include "SimpleActivity.h"
#include "PixelSettings.h"

class SolidActivity : SimpleActivity<PixelSettings>
{
public:
    SolidActivity(PixelSettings settings)
        : SimpleActivity(settings) {}
    // overrides
    virtual bool Pulse();
    virtual void Setup();
    virtual void Reset();
    virtual void Tick() {}
};
