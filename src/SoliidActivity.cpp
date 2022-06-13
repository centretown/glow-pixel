// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "SolidActivity.h"

bool SolidActivity::Pulse()
{
    if (Dead())
    {
        Reset();
        return false;
    }
    return true;
}

void SolidActivity::Setup()
{
}

void SolidActivity::Reset()
{
}
