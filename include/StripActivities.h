// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"
#include "SelectActivity.h"
#include "StripSettings.h"

#define ACTIVITY_COUNT 1

class StripActivities : public SelectActivity<StripSettings>
{
private:
    /* data */
public:
    StripActivities(
        StripSettings &settings)
        : SelectActivity(ACTIVITY_COUNT, settings) {}
    ~StripActivities() {}
};