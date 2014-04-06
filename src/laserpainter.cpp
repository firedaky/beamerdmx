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

#include <QPainter>

#include "colors.h"
#include "laserpainter.h"

LaserPainter::LaserPainter(QObject *parent) :
    QObject(parent),
    primaryColor(Colors::Black),
    secondaryColor(Colors::Black)
{
}

LaserPainter::LaserPainter(QColor primary, QColor secondary, QObject *parent) :
    QObject(parent),
    primaryColor(primary),
    secondaryColor(secondary)
{

}

void LaserPainter::paint(QPainter *painter, QRectF boundingRect)
{
    painter->fillRect(boundingRect, primaryColor);
}