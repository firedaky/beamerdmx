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

#include "paintermanager.h"
#include "lasersurface.h"

#include "painters/blackoutpainter.h"

static const int NUM_PAINTER_FOLDERS = 64;
static const int NUM_PAINTER_FILES = 32;

PainterManager::PainterManager(QObject *parent) :
    QObject(parent),
    currentPainter(nullptr),
    surface(nullptr),
    currentFile(0),
    currentFolder(0)
{
}

PainterManager::~PainterManager()
{
    if (surface)
    {
        surface->setLaserPainter(nullptr);
    }
}

bool PainterManager::initialize(LaserSurface* surface)
{
    if (!surface)
    {
        qCritical() << "Invalid laser surface passed";
        return false;
    }

    // Load all painters
    for (int folder = 0; folder < NUM_PAINTER_FOLDERS; ++folder)
    {
        for (int file = 0; file < NUM_PAINTER_FILES; ++file)
        {
            painters.push_back(new BlackoutPainter(this));
        }
    }

    currentPainter = painters[0];
    this->surface = surface;
    surface->setLaserPainter(currentPainter);

    return true;
}

void PainterManager::onChangePainter(int newFolder, int newFile)
{
    if ((newFolder != currentFolder) || (newFile != currentFile))
    {
        currentFolder = newFolder;
        currentFile = newFile;

        LaserPainter* oldPainter = currentPainter;

        currentPainter = painters[currentFolder * NUM_PAINTER_FILES + currentFile];
        currentPainter->restart();
        currentPainter->onPrimaryColorUpdated(overridePrimary, primaryOverrideColor);
        currentPainter->onSecondaryColorUpdated(overrideSecondary, secondaryOverrideColor);
        currentPainter->onBpmChanged(bpm);
        currentPainter->onTick(runningTime, deltaTime);

        surface->setLaserPainter(currentPainter);
        oldPainter->stop();
    }
}

void PainterManager::onPrimaryColorUpdated(bool override, QColor newColor)
{
    overridePrimary = override;
    primaryOverrideColor = newColor;

    currentPainter->onPrimaryColorUpdated(override, newColor);
}

void PainterManager::onSecondaryColorUpdated(bool override, QColor newColor)
{
    overrideSecondary = override;
    secondaryOverrideColor = newColor;

    currentPainter->onSecondaryColorUpdated(override, newColor);
}

void PainterManager::onBpmChanged(qreal newValue)
{
    bpm = newValue;

    currentPainter->onBpmChanged(newValue);
}

void PainterManager::onTick(double runningTime, double deltaTime)
{
    this->runningTime = runningTime;
    this->deltaTime = deltaTime;

    currentPainter->onTick(runningTime, deltaTime);
}
