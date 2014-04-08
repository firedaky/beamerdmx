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
    memset(dmxValues, 0, sizeof(dmxValues));
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

void LaserController::onDimmerChanged(qreal newValue)
{
    dmxValues[static_cast<uint32_t>(DmxChannels::DIMMER)] = static_cast<uint8_t>(newValue);

    emit dimmerChanged(newValue / 255.0);
}

void LaserController::onPanCoarseChanged(qreal newValue)
{
    dmxValues[static_cast<uint32_t>(DmxChannels::PAN)] = static_cast<uint8_t>(newValue);

    updatePan();
}

void LaserController::onPanFineChanged(qreal newValue)
{
    dmxValues[static_cast<uint32_t>(DmxChannels::PAN_FINE)] = static_cast<uint8_t>(newValue);

    updatePan();
}

void LaserController::onTiltCoarseChanged(qreal newValue)
{
    dmxValues[static_cast<uint32_t>(DmxChannels::TILT)] = static_cast<uint8_t>(newValue);

    updateTilt();
}

void LaserController::onTiltFineChanged(qreal newValue)
{
    dmxValues[static_cast<uint32_t>(DmxChannels::TILT_FINE)] = static_cast<uint8_t>(newValue);

    updateTilt();
}

void LaserController::onZoomChanged(qreal newValue)
{
    dmxValues[static_cast<uint32_t>(DmxChannels::ZOOM)] = static_cast<uint8_t>(newValue);

    emit zoomChanged(newValue / 255.0);
}

void LaserController::updatePan()
{
    uint8_t panCoarse = dmxValues[static_cast<uint32_t>(DmxChannels::PAN)];
    uint8_t panFine   = dmxValues[static_cast<uint32_t>(DmxChannels::PAN_FINE)];

    int32_t pan16Bit = (panCoarse << 8) + panFine;
    qreal newPan = (2.0 * (pan16Bit / 65535.0)) - 1.0f;

    emit panChanged(newPan);
}

void LaserController::updateTilt()
{
    uint8_t tiltCoarse = dmxValues[static_cast<uint32_t>(DmxChannels::TILT)];
    uint8_t tiltFine   = dmxValues[static_cast<uint32_t>(DmxChannels::TILT_FINE)];

    int32_t tilt16Bit = (tiltCoarse << 8) + tiltFine;
    qreal newTilt = (2.0 * (tilt16Bit / 65535.0)) - 1.0f;

    emit tiltChanged(newTilt);
}
