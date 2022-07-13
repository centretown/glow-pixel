// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "wait.h"

void wait(uint32_t ms)
{
#ifdef ARDUINO
    delay(ms);
#endif
}
