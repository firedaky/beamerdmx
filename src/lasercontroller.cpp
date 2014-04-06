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

#include <QDebug>

#include "channels.h"
#include "colors.h"

#include "lasersurface.h"
#include "laserpainter.h"
#include "lasercontroller.h"

LaserController::LaserController(QObject *parent) :
    QObject(parent),
    laserSurface(nullptr),
    blackoutPainter(nullptr)
{
}

LaserController::~LaserController()
{
    if (laserSurface)
    {
        laserSurface->setLaserPainter(nullptr);
    }
}

bool LaserController::initialize(LaserSurface *surface)
{
    if (!surface)
    {
        qCritical() << "Invalid LaserSurface";
        return false;
    }

    laserSurface = surface;

    blackoutPainter = new LaserPainter(this);

    laserSurface->setLaserPainter(blackoutPainter);

    return true;
}
