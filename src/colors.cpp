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

#include "colors.h"

namespace Colors
{

QColor Red        = QColor(255,   0,   0);
QColor Amber      = QColor(255, 128,   0);
QColor Yellow     = QColor(255, 255,   0);
QColor LightGreen = QColor(128, 255,   0);
QColor Green      = QColor(  0, 255,   0);
QColor Cyan       = QColor(  0, 255, 255);
QColor LightBlue  = QColor(  0, 182, 255);
QColor Blue       = QColor(  0,   0, 255);
QColor Magenta    = QColor(255,   0, 255);
QColor Pink       = QColor(255,   0, 128);
QColor White      = QColor(255, 255, 255);
QColor Black      = QColor(  0,   0,   0);

QColor RainbowColors[] = {
    Red,
    Amber,
    Yellow,
    LightGreen,
    Green,
    Cyan,
    LightBlue,
    Blue,
    Magenta,
    Pink,
    White
};

const int RainbowColorCount = sizeof(RainbowColors) / sizeof(RainbowColors[0]);

}
