// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "PixelController.h"

namespace glow
{
    // PixelController controller(pixelWriters, pixelWritersCount);

    PixelController::PixelController(PixelWriter **writers, size_t length)
        : writers(writers), length(length)
    {
        for (size_t i = 0; i < length; i++)
        {
            count += writers[i]->Length();
        }
    }

    void PixelController::Setup()
    {
        for (size_t i = 0; i < length; i++)
        {
            writers[i]->Setup();
        }
    }

    void PixelController::Put(uint16_t index, PixelColor &color)
    {
        size_t extent = 0;
        size_t offset = 0;
        for (size_t i = 0; i < length; i++)
        {
            PixelWriter *p = writers[i];
            extent += p->Length();
            if (index < extent)
            {
                p->Put(index - offset, color);
                return;
            }
            offset = extent;
        }
    }

    void PixelController::Update(uint16_t begin, uint16_t end)
    {
        size_t extent = 0;
        for (size_t i = 0; i < length; i++)
        {
            bool updated = false;
            PixelWriter *p = writers[i];
            extent += p->Length();
            if (begin < extent)
            {
                p->Update();
                updated = true;
            }
            if (end < extent)
            {
                if (updated == false)
                {
                    p->Update();
                }
                return;
            }
        }
    }
}
