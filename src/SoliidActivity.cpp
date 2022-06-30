// Copyright (c) 2022 Dave Marsh. See LICENSE.

// #include "SolidActivity.h"
// namespace strip
// {
//     bool SolidActivity::Pulse()
//     {
//         if (Dead())
//         {
//             Reset();
//         }
//         return false;
//     }

//     void SolidActivity::Tick()
//     {
//         for (uint16_t i = 0; i < pixel.Count(); i++)
//         {
//             pixel.Put(i);
//         }

//         pixel.Update();
//     }

//     void SolidActivity::Reset()
//     {
//         settings.Color().RGBW(0, 0, 0, 0);
//         for (uint16_t i = 0; i < settings.Count(); i++)
//         {
//             pixel.Put(i);
//         }
//         pixel.Update();
//     }
// }
