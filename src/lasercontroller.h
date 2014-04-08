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

#include <QObject>

#include "channels.h"

class LaserSurface;
class LaserPainter;

class LaserController : public QObject
{
    Q_OBJECT
public:
    explicit LaserController(QObject *parent = 0);
    virtual ~LaserController();

    bool initialize(LaserSurface* surface);

signals:
    void dimmerChanged(qreal newValue);
    void panChanged(qreal newValue);
    void tiltChanged(qreal newValue);
    void zoomChanged(qreal newValue);

public slots:
    void onDimmerChanged(qreal newValue);
    void onPanCoarseChanged(qreal newValue);
    void onPanFineChanged(qreal newValue);
    void onTiltCoarseChanged(qreal newValue);
    void onTiltFineChanged(qreal newValue);
    void onZoomChanged(qreal newValue);

protected:
    void updatePan();
    void updateTilt();

    LaserSurface* laserSurface;
    LaserPainter* blackoutPainter;    

    uint8_t dmxValues[static_cast<uint32_t>(DmxChannels::CHANNEL_COUNT)];
};
