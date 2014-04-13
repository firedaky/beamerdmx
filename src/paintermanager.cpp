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
#include "colors.h"

#include "painters/blackoutpainter.h"
#include "painters/standingwave.h"

static const int NUM_PAINTER_FOLDERS = 64;
static const int NUM_PAINTER_FILES = 32;

static int indexOf(int folder, int file)
{
    return folder * NUM_PAINTER_FILES + file;
}

PainterManager::PainterManager(QObject *parent) :
    QObject(parent),
    blackoutPainter(nullptr),
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
    painters.resize(NUM_PAINTER_FILES * NUM_PAINTER_FOLDERS, nullptr);
    blackoutPainter = new BlackoutPainter(this);

    // Wave painters (Folder 4)
    painters[indexOf(3, 0)] = new StaticStandingWavePainter(Colors::Red,     this);
    painters[indexOf(3, 1)] = new StaticStandingWavePainter(Colors::Green,   this);
    painters[indexOf(3, 2)] = new StaticStandingWavePainter(Colors::Blue,    this);
    painters[indexOf(3, 3)] = new StaticStandingWavePainter(Colors::Cyan,    this);
    painters[indexOf(3, 4)] = new StaticStandingWavePainter(Colors::Magenta, this);
    painters[indexOf(3, 5)] = new StaticStandingWavePainter(Colors::Yellow,  this);

    painters[indexOf(3,  6)] = new AMStandingWavePainter(Colors::Red,     this);
    painters[indexOf(3,  7)] = new AMStandingWavePainter(Colors::Green,   this);
    painters[indexOf(3,  8)] = new AMStandingWavePainter(Colors::Blue,    this);
    painters[indexOf(3,  9)] = new AMStandingWavePainter(Colors::Cyan,    this);
    painters[indexOf(3, 10)] = new AMStandingWavePainter(Colors::Magenta, this);
    painters[indexOf(3, 11)] = new AMStandingWavePainter(Colors::Yellow,  this);

    // Initialize all painters
    for (size_t i = 0; i < painters.size(); ++i)
    {
        if (!painters[i]) continue;

        if (!painters[i]->initialize())
        {
            delete painters[i];
            painters[i] = blackoutPainter;
        }
    }

    currentPainter = painters[0];
    if (!currentPainter) currentPainter = blackoutPainter;
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
        if (!currentPainter) currentPainter = blackoutPainter;
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
