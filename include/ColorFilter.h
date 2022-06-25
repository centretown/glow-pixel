// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "PixelColor.h"

namespace glow
{
    class ColorFilter
    {
    private:
        ColorFilter *next = NULL;

    public:
        PixelColor &Apply(PixelColor &source, PixelColor &color)
        {
            PixelColor worker(source);
            for (ColorFilter *current = this;
                 current != NULL;
                 current = current->next)
            {
                current->apply(worker, worker);
            }

            color.Copy(worker);
            return color;
        }

        inline void Link(ColorFilter *filter)
        {
            ColorFilter *link = this;
            for (ColorFilter *current = this;
                 current != NULL;
                 current = current->next)
            {
                // cant't link filter more than once
                if (filter == current)
                {
                    return;
                }
                link = current;
            }
            link->next = filter;
        }

        inline void UnLink()
        {
            for (ColorFilter *current = this;
                 current != NULL;)
            {
                ColorFilter *hold = current->next;
                current->next = NULL;
                current = hold;
            }
        }

    private:
        virtual void apply(PixelColor &source, PixelColor &color) = 0;
    };
}