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
    primaryColor(Colors::Blue),
    secondaryColor(Colors::Black),
    primaryOverrideColor(Colors::Black),
    secondaryOverrideColor(Colors::Black),
    overridePrimary(false),
    overrideSecondary(false),
    bpm(0),
    runningTime(0.0),
    deltaTime(0.0)
{
}

LaserPainter::LaserPainter(QColor primary, QColor secondary, QObject *parent) :
    QObject(parent),
    primaryColor(primary),
    secondaryColor(secondary),
    primaryOverrideColor(primary),
    secondaryOverrideColor(secondary),
    overridePrimary(false),
    overrideSecondary(false),
    bpm(0),
    runningTime(0.0),
    deltaTime(0.0)
{

}

bool LaserPainter::initialize()
{
    return true;
}

void LaserPainter::paint(QPainter *painter, QRectF boundingRect)
{
    painter->fillRect(boundingRect, overridePrimary ? primaryOverrideColor : primaryColor);
    painter->setPen(overrideSecondary ? secondaryOverrideColor : secondaryColor);
    painter->drawEllipse(boundingRect);
}

void LaserPainter::onPrimaryColorUpdated(bool override, QColor newColor)
{
    overridePrimary = override;
    primaryOverrideColor = newColor;
}

void LaserPainter::onSecondaryColorUpdated(bool override, QColor newColor)
{
    overrideSecondary = override;
    secondaryOverrideColor = newColor;
}

void LaserPainter::onBpmChanged(qreal newValue)
{
    bpm = newValue;
}

void LaserPainter::onTick(double runningTime, double deltaTime)
{
    this->runningTime = runningTime;
    this->deltaTime = deltaTime;
}
