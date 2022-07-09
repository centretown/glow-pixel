// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

template <typename T, typename U, typename V, typename W>
void Looper(T compare, U put, V increment, W reset)
{
    while (compare())
    {
        put();
        increment();
    }
    reset();
}
