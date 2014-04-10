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

#include <vector>

#include <QObject>
#include <QColor>

class LaserPainter;
class LaserSurface;

class PainterManager : public QObject
{
    Q_OBJECT
public:
    explicit PainterManager(QObject *parent = 0);
    virtual ~PainterManager();

    bool initialize(LaserSurface *surface);

signals:

public slots:
    void onChangePainter(int newFolder, int newFile);
    void onPrimaryColorUpdated(bool override, QColor newColor);
    void onSecondaryColorUpdated(bool override, QColor newColor);
    void onBpmChanged(qreal newValue);
    void onTick(double runningTime, double deltaTime);

protected:
    std::vector<LaserPainter*> painters;
    LaserPainter* currentPainter;
    LaserSurface* surface;
    int currentFile;
    int currentFolder;

    QColor primaryOverrideColor;
    QColor secondaryOverrideColor;
    bool overridePrimary;
    bool overrideSecondary;
    qreal bpm;
    qreal runningTime;
    qreal deltaTime;
};
