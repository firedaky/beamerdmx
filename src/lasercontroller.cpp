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
#include "painters/laserpainter.h"
#include "painters/blackoutpainter.h"
#include "lasercontroller.h"

LaserController::LaserController(QObject *parent) :
    QObject(parent),
    laserSurface(nullptr),
    currentPainter(nullptr),
    blackoutPainter(nullptr),
    runningTime(0.0),
    deltaTime(0.0),
    shutterState(false),
    nextShutterToggleTime(-1.0),
    shutterChannelChanged(false),
    rotation(0.0),
    rotationRate(0.0),
    overridePrimaryColor(false),
    overrideSecondaryColor(false),
    primaryColor(Colors::Black),
    secondaryColor(Colors::Black)
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

    blackoutPainter = new BlackoutPainter(this);
    currentPainter = blackoutPainter;

    laserSurface->setLaserPainter(currentPainter);

    timeSource = QTime::currentTime();

    connect(&tickSource, SIGNAL(timeout()), SLOT(onTick()));
    tickSource.setTimerType(Qt::PreciseTimer);

    timeSource.start();
    tickSource.start(25);

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

void LaserController::onStrobeChanged(qreal newValue)
{
    dmxValues[static_cast<uint32_t>(DmxChannels::STROBE)] = static_cast<uint8_t>(newValue);
    shutterChannelChanged = true;
}

void LaserController::onRotationCoarseChanged(qreal newValue)
{
    dmxValues[static_cast<uint32_t>(DmxChannels::ROTATION)] = static_cast<uint8_t>(newValue);
}

void LaserController::onRotationFineChanged(qreal newValue)
{
    dmxValues[static_cast<uint32_t>(DmxChannels::ROTATION_FINE)] = static_cast<uint8_t>(newValue);
}

void LaserController::onColor1Changed(qreal newValue)
{
    dmxValues[static_cast<uint32_t>(DmxChannels::COLOR1)] = static_cast<uint8_t>(newValue);
    primaryColorChannelChanged = true;
}

void LaserController::onColor2Changed(qreal newValue)
{
    dmxValues[static_cast<uint32_t>(DmxChannels::COLOR2)] = static_cast<uint8_t>(newValue);
    secondaryColorChannelChanged = true;
}

void LaserController::onRedChanged(qreal newValue)
{
    dmxValues[static_cast<uint32_t>(DmxChannels::RED)] = static_cast<uint8_t>(newValue);
}

void LaserController::onGreenChanged(qreal newValue)
{
    dmxValues[static_cast<uint32_t>(DmxChannels::GREEN)] = static_cast<uint8_t>(newValue);
}

void LaserController::onBlueChanged(qreal newValue)
{
    dmxValues[static_cast<uint32_t>(DmxChannels::BLUE)] = static_cast<uint8_t>(newValue);
}

void LaserController::onBpmChanged(qreal newValue)
{
    dmxValues[static_cast<uint32_t>(DmxChannels::BPM)] = static_cast<uint8_t>(newValue);

    currentPainter->onBpmChanged(newValue);
}

void LaserController::onFolderChanged(qreal newValue)
{
    dmxValues[static_cast<uint32_t>(DmxChannels::FOLDER)] = static_cast<uint8_t>(newValue);
}

void LaserController::onFileChanged(qreal newValue)
{
    dmxValues[static_cast<uint32_t>(DmxChannels::FILE)] = static_cast<uint8_t>(newValue);
}

void LaserController::onTick()
{
    double newTime = timeSource.elapsed() / 1000.0;
    deltaTime = newTime - runningTime;
    runningTime = newTime;

    updateShutter();
    updateRotation();
    updateColors();

    currentPainter->onTick(runningTime, deltaTime);

    laserSurface->update();
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

void LaserController::updateShutter()
{
    uint8_t shutterChannel = dmxValues[static_cast<uint32_t>(DmxChannels::STROBE)];

    if (shutterChannel < 16)
    {
        shutterState = false;
        nextShutterToggleTime = -1;
    }
    else if (shutterChannel < 129)
    {
        double rate = ((shutterChannel - 16.0) / (128 - 16)) * 9.0 + 1.0;
        double delta = 0.5 / rate;

        if (nextShutterToggleTime > 0)
        {
            if (nextShutterToggleTime <= runningTime)
            {
                shutterState = !shutterState;
                nextShutterToggleTime += delta;
            }
        }
        else
        {
            shutterState = false;
            nextShutterToggleTime = runningTime + delta;
        }

        if (shutterChannelChanged)
        {
            nextShutterToggleTime = runningTime + delta;
        }
    }
    else if (shutterChannel < 240)
    {
        double rate = ((shutterChannel - 129.0) / (239 - 129)) * 9.0 + 1.0;
        double delta = 0.5 / rate;

        if (nextShutterToggleTime > 0)
        {
            if (nextShutterToggleTime <= runningTime)
            {
                if (!shutterState)
                {
                    nextShutterToggleTime = runningTime + 0.05;
                }
                else
                {
                    double scaler = qrand();
                    scaler /= RAND_MAX;
                    scaler *= 5.0;
                    scaler += 1;

                    nextShutterToggleTime += delta * scaler;
                }

                shutterState = !shutterState;
            }
        }
        else
        {
            shutterState = false;
            nextShutterToggleTime = runningTime + delta;
        }

        if (shutterChannelChanged)
        {
            nextShutterToggleTime = runningTime + delta;
        }
    }
    else if (shutterChannel >= 240)
    {
        shutterState = true;
        nextShutterToggleTime = -1;
    }

    emit shutterChanged(shutterState);
    shutterChannelChanged = false;
}

void LaserController::updateRotation()
{
    static const int32_t rotationCWMax  = (126 << 8) + 255;
    static const int32_t rotationCCWMin = (129 << 8) +   0;
    static const double maxRPM = 2 * 360;

    uint8_t rotationCoarse = dmxValues[static_cast<uint32_t>(DmxChannels::ROTATION)];
    uint8_t rotationFine   = dmxValues[static_cast<uint32_t>(DmxChannels::ROTATION_FINE)];

    int32_t rotation16Bit = (rotationCoarse << 8) + rotationFine;
    qreal angle = 0.0;

    // Check for index or rotating mode
    if (dmxValues[static_cast<uint32_t>(DmxChannels::FILE)] < 128)
    {
        // Indexed mode
        angle = (2.0 * (rotation16Bit / 65535.0)) - 1.0f;
        angle *= 180;
    }
    else
    {
        // Rotating mode
        if (rotation16Bit <= rotationCWMax)
        {
            double scaler = 1.0 - (rotation16Bit / (double)rotationCWMax);
            rotationRate = maxRPM * scaler;
        }
        else if (rotation16Bit >= rotationCCWMin)
        {
            double scaler = (rotation16Bit - rotationCCWMin) / (65535.0 - rotationCCWMin);
            rotationRate = -maxRPM * scaler;
        }
        else
        {
            rotationRate = 0;
        }


        angle = rotation + rotationRate * deltaTime;

        while (angle >  180) angle -= 360;
        while (angle < -180) angle += 360;
    }

    rotation = angle;

    emit angleChanged(rotation);
}

void LaserController::updateColors()
{

    updateColorsHelper(dmxValues[static_cast<uint32_t>(DmxChannels::COLOR1)],
            overridePrimaryColor,
            primaryColor,
            primaryRainbowIndex,
            nextPrimaryRainbowTime,
            primaryColorChannelChanged);
    currentPainter->onPrimaryColorUpdated(overridePrimaryColor, primaryColor);
    primaryColorChannelChanged = false;

    updateColorsHelper(dmxValues[static_cast<uint32_t>(DmxChannels::COLOR2)],
            overrideSecondaryColor,
            secondaryColor,
            secondaryRainbowIndex,
            nextSecondaryRainbowTime,
            secondaryColorChannelChanged);
    currentPainter->onSecondaryColorUpdated(overrideSecondaryColor, secondaryColor);
    secondaryColorChannelChanged = false;
}

void LaserController::updateColorsHelper(uint8_t channelValue, bool &override, QColor &color, int &rainbowIndex, double &nextRainbowTime, bool channelChanged)
{
    if (channelValue < 8)
    {
        override = false;
        color = Colors::Black;
        rainbowIndex = 0;
        nextRainbowTime = -1;
    }
    else
    {
        override = true;

        if (channelValue < 16)
        {
            color = QColor(dmxValues[static_cast<uint32_t>(DmxChannels::RED)],
                           dmxValues[static_cast<uint32_t>(DmxChannels::GREEN)],
                           dmxValues[static_cast<uint32_t>(DmxChannels::BLUE)]);
            rainbowIndex = 0;
            nextRainbowTime = -1;
        }
        else if (channelValue < 24)
        {
            color = Colors::Red;
            rainbowIndex = 0;
            nextRainbowTime = -1;
        }
        else if (channelValue < 32)
        {
            color = Colors::Amber;
            rainbowIndex = 1;
            nextRainbowTime = -1;
        }
        else if (channelValue < 40)
        {
            color = Colors::Yellow;
            rainbowIndex = 2;
            nextRainbowTime = -1;
        }
        else if (channelValue < 48)
        {
            color = Colors::LightGreen;
            rainbowIndex = 3;
            nextRainbowTime = -1;
        }
        else if (channelValue < 56)
        {
            color = Colors::Green;
            rainbowIndex = 4;
            nextRainbowTime = -1;
        }
        else if (channelValue < 64)
        {
            color = Colors::Cyan;
            rainbowIndex = 5;
            nextRainbowTime = -1;
        }
        else if (channelValue < 72)
        {
            color = Colors::LightBlue;
            rainbowIndex = 6;
            nextRainbowTime = -1;
        }
        else if (channelValue < 80)
        {
            color = Colors::Blue;
            rainbowIndex = 7;
            nextRainbowTime = -1;
        }
        else if (channelValue < 96)
        {
            color = Colors::Magenta;
            rainbowIndex = 8;
            nextRainbowTime = -1;
        }
        else if (channelValue < 96)
        {
            color = Colors::Pink;
            rainbowIndex = 9;
            nextRainbowTime = -1;
        }
        else if (channelValue < 128)
        {
            color = Colors::White;
            rainbowIndex = 10;
            nextRainbowTime = -1;
        }
        else if (channelValue < 192)
        {
            double rate = ((channelValue - 128.0) / (191 - 128)) * -1.0;
            double delta = 1.0 / (1.0 + rate);
            delta /= 20.0;

            if (nextRainbowTime > 0)
            {
                if (nextRainbowTime <= runningTime)
                {
                    if (++rainbowIndex >= Colors::RainbowColorCount) rainbowIndex = 0;
                    nextRainbowTime += delta;
                }
            }
            else
            {
                nextRainbowTime = runningTime + delta;
            }

            if (channelChanged)
            {
                nextRainbowTime = runningTime + delta;
            }

            color = Colors::RainbowColors[rainbowIndex];
        }
        else
        {
            double rate = ((channelValue - 192.0) / (255 - 192));
            double delta = 1.0 / rate;
            delta /= 20.0;

            if (nextRainbowTime > 0)
            {
                if (nextRainbowTime <= runningTime)
                {
                    if (--rainbowIndex < 0) rainbowIndex = Colors::RainbowColorCount - 1;
                    nextRainbowTime += delta;
                }
            }
            else
            {
                nextRainbowTime = runningTime + delta;
            }

            if (channelChanged)
            {
                nextRainbowTime = runningTime + delta;
            }

            color = Colors::RainbowColors[rainbowIndex];
        }
    }
}
