//   Copyright 2014 Lukas Erlinghagen

//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at

//       http://www.apache.org/licenses/LICENSE-2.0

//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.

#pragma once

#include <cstdint>

enum class DmxChannels: uint32_t
{
    DIMMER = 1,
    PAN,
    TILT,
    COLOR1,
    COLOR2,
    RED,
    GREEN,
    BLUE,
    FOLDER,
    FILE,
    ROTATION,
    ZOOM,
    STROBE,
    BPM,
    PAN_FINE,
    TILT_FINE,
    ROTATION_FINE
};

/*
 * DMX Protocol
 *
 *  1 - Dimmer:
 *        0 - 255 Dimmer 0% - 100%
 *
 *  2 - Pan: Coarse
 *        0 - 255 Right to left (seen from Projector)
 *
 *  3 - Tilt: Coarse
 *        0 - 255 Top to bottom
 *
 *  4 - Color 1: Main color override
 *        0 -   7 No override
 *        8 -  15 From RGB channels
 *       16 -  23 Red
 *       24 -  31 Amber
 *       32 -  39 Yellow
 *       40 -  47 Light Green
 *       48 -  55 Green
 *       56 -  63 Cyan
 *       64 -  71 Light Blue
 *       72 -  79 Blue
 *       80 -  87 Magenta
 *       88 -  95 Pink
 *       96 - 127 Open/White
 *      128 - 191 Rainbow Forward Fast - Slow
 *      192 - 255 Rainbow Backward Slow - Fast
 *
 *  5 - Color 2: Secondary color override
 *        0 -   7 No override
 *        8 -  15 From RGB channels
 *       16 -  23 Red
 *       24 -  31 Amber
 *       32 -  39 Yellow
 *       40 -  47 Light Green
 *       48 -  55 Green
 *       56 -  63 Cyan
 *       64 -  71 Light Blue
 *       72 -  79 Blue
 *       80 -  87 Magenta
 *       88 -  95 Pink
 *       96 - 127 Open/White
 *      128 - 191 Rainbow Forward Fast - Slow
 *      192 - 255 Rainbow Backward Slow - Fast
 *
 *  6 - Red:
 *        0 - 255 Red 0% - 100%
 *
 *  7 - Green:
 *        0 - 255 Green 0% - 100%
 *
 *  8 - Blue:
 *        0 - 255 Blue 0% - 100%
 *
 *  9 - Folder: 64 Folders, 32 Presets, 32 User-defined
 *        0 -   3 Folder  1 (Flower)
 *        4 -   7 Folder  2 (Cone)
 *        8 -  11 Folder  3 (Plane)
 *       12 -  15 Folder  4 (Wave)
 *       16 -  19 Folder  5 (Starfield)
 *       20 -  23 Folder  6 (Strokes)
 *       24 -  27 Folder  7 (Complex pattern)
 *       28 -  31 Folder  8 (Strobe)
 *       32 -  35 Folder  9 (Characters 1)
 *       36 -  39 Folder 10 (Characters 2)
 *       40 -  43 Folder 11 (Reserved)
 *      ...
 *      128 - 131 Folder 32 (User 1)
 *      132 - 135 Folder 33 (User 2)
 *      ...
 *
 * 10 - File: 32 Files, Indexed or Rotating
 *        0 -   3 File 1 (Indexed)
 *        4 -   7 File 2 (Indexed)
 *      ...
 *      128 - 131 File 1 (Rotating)
 *      132 - 135 File 2 (Rotating)
 *      ...
 *
 * 11 - Rotation: Index or Rotation
 *        0 - 255 -180° - 180° in Indexed mode
 *        0 - 126 Rotation CW in Rotating mode, seen from projector, fast - slow
 *      127 - 128 Rotation stop in Rotating mode
 *      129 - 255 Rotation CCW in Rotating mode, seen from projector, slow - fast
 *
 * 12 - Zoom:
 *        0 - 255 Zoom 0% - 100%
 *
 * 13 - Strobe:
 *        0 -  15 Closed
 *       16 - 128 Random Strobe slow - fast
 *      129 - 239 Strobe slow - fast
 *      240 - 255 Open
 *
 * 14 - BPM: Effect speed in BPM if supported by effect
 *        0 - 255 BPM
 *
 * 15 - Pan Fine:
 *        0 - 255 Pan LSB
 *
 * 16 - Tilt Fine:
 *        0 - 255 Tilt LSB
 *
 * 17 - Rotation Fine:
 *        0 - 255 Rotation LSB
 */
