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

#include "laserpainter.h"

class StaticStandingWavePainter : public LaserPainter
{
    Q_OBJECT
public:
    explicit StaticStandingWavePainter(QObject *parent = 0);
    StaticStandingWavePainter(QColor color, QObject* parent = 0);

    virtual void paint(QPainter* painter, QRectF boundingRect);

signals:

public slots:

};

class AMStandingWavePainter : public LaserPainter
{
    Q_OBJECT
public:
    explicit AMStandingWavePainter(QObject *parent = 0);
    AMStandingWavePainter(QColor color, QObject* parent = 0);

    virtual void paint(QPainter* painter, QRectF boundingRect);

signals:

public slots:

};
