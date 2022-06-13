// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "PixelGroup.h"

PixelGroup::PixelGroup(PixelWriter **writers, size_t length)
    : writers(writers), length(length)
{
    for (size_t i = 0; i < length; i++)
    {
        count += writers[i]->Length();
    }
}

PixelGroup::~PixelGroup()
{
}

void PixelGroup::Setup()
{
    for (size_t i = 0; i < length; i++)
    {
        writers[i]->Setup();
    }
}

void PixelGroup::Put(uint16_t index, uint8_t red, uint8_t green, uint8_t blue)
{
    size_t extent = 0;
    size_t offset = 0;
    for (size_t i = 0; i < length; i++)
    {
        PixelWriter *p = writers[i];
        extent += p->Length();
        if (index < extent)
        {
            p->Put(index - offset, red, green, blue);
            return;
        }
        offset = extent;
    }
}

void PixelGroup::Update(uint16_t begin, uint16_t end)
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
