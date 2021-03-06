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

#define _USE_MATH_DEFINES
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include <QObject>
#include <QRectF>
#include <QColor>
#include <QPainter>

static const float DEFAULT_LINE_THICKNESS = 7;

class QPainter;

class LaserPainter : public QObject
{
    Q_OBJECT
public:
    explicit LaserPainter(QObject *parent = 0);
    LaserPainter(QColor primary, QColor secondary, QObject* parent = 0);

    virtual bool initialize();
    virtual void restart();
    virtual void stop();

    virtual void paint(QPainter* painter, QRectF boundingRect) = 0;

signals:

public slots:
    void onPrimaryColorUpdated(bool override, QColor newColor);
    void onSecondaryColorUpdated(bool override, QColor newColor);
    void onBpmChanged(qreal newValue);
    void onTick(double runningTime, double deltaTime);

protected:
    QColor primaryColor;
    QColor secondaryColor;
    QColor primaryOverrideColor;
    QColor secondaryOverrideColor;
    bool overridePrimary;
    bool overrideSecondary;
    qreal bpm;
    qreal runningTime;
    qreal deltaTime;
};
