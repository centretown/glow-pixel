// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "PixelController.h"

namespace glow
{
    // PixelController controller(pixelWriters, pixelWritersCount);

    PixelController::PixelController(PixelWriter **writers, size_t writerCount)
        : writers(writers), writerCount(writerCount)
    {
        if (writerCount > MAX_PIXEL_WRITERS)
        {
            writerCount = MAX_PIXEL_WRITERS;
        }

        for (size_t i = 0; i < writerCount; i++)
        {
            pixelCount += writers[i]->Length();
            partitions[i] = pixelCount;
        }
    }

    void PixelController::Setup()
    {
        for (size_t i = 0; i < writerCount; i++)
        {
            writers[i]->Setup();
        }
    }

    void PixelController::Put(uint16_t index, PixelColor &color)
    {
        index %= pixelCount;
        size_t writerIndex = findWriterIndex(index);
        if (writerIndex > 0)
        {
            index -= partitions[writerIndex - 1];
        }
        writers[writerIndex]->Put(index, color);
    }

    void PixelController::Update()
    {
        for (size_t i = 0; i < writerCount; i++)
        {
            if (mustUpdate(i))
            {
                writers[i]->Update();
            }
        }
        updateDone();
    }
}
