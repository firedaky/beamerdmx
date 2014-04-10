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

#include "painters/laserpainter.h"
#include "lasersurface.h"

LaserSurface::LaserSurface(QQuickItem *parent) :
    QQuickPaintedItem(parent),
    laserPainter(nullptr)
{
}

void LaserSurface::paint(QPainter *painter)
{
    if (laserPainter)
    {
        laserPainter->paint(painter, contentsBoundingRect());
    }
    else
    {
#ifdef DEBUG
        // In debug builds, we warn about an unset laser painter by turning the screen magenta.
        painter->fillRect(contentsBoundingRect(), Qt::magenta);
#else
        painter->fillRect(contentsBoundingRect(), Qt::black);
#endif
    }
}

void LaserSurface::setLaserPainter(LaserPainter *newPainter)
{
    laserPainter = newPainter;
}
