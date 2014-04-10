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

#include "standingwave.h"

static const float WAVE_FREQUENCY = 2;
static const float WAVE_SWING = 0.5f;
static const float DRAW_EVERY_NTH = 10;

StaticStandingWavePainter::StaticStandingWavePainter(QObject *parent) :
    LaserPainter(parent)
{
}

StaticStandingWavePainter::StaticStandingWavePainter(QColor color, QObject *parent) :
    LaserPainter(parent)
{
    primaryColor = color;
}

void StaticStandingWavePainter::paint(QPainter *painter, QRectF boundingRect)
{
    QColor color = overridePrimary ? primaryOverrideColor : primaryColor;
    QPen pen(color, DEFAULT_LINE_THICKNESS, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(pen);

    auto centerV = (boundingRect.bottom() - boundingRect.top()) / 2;

    float dU = boundingRect.left();
    float step = DRAW_EVERY_NTH;

    QPainterPath sinePath;
    sinePath.moveTo(dU, centerV);

    for (float u = 0; u < boundingRect.width(); u += step)
    {
        float t = (u / boundingRect.width()) * WAVE_FREQUENCY;
        float amplitude = (WAVE_SWING / 2) * sin(M_PI * 2 * t);

        sinePath.lineTo(u + dU, centerV * (1 + amplitude));
    }

    painter->drawPath(sinePath);
}

AMStandingWavePainter::AMStandingWavePainter(QObject *parent) :
    LaserPainter(parent)
{
}

AMStandingWavePainter::AMStandingWavePainter(QColor color, QObject *parent) :
    LaserPainter(parent)
{
    primaryColor = color;
}

void AMStandingWavePainter::paint(QPainter *painter, QRectF boundingRect)
{
    QColor color = overridePrimary ? primaryOverrideColor : primaryColor;
    QPen pen(color, DEFAULT_LINE_THICKNESS, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(pen);

    auto centerV = (boundingRect.bottom() - boundingRect.top()) / 2;

    float dU = boundingRect.left();
    float step = DRAW_EVERY_NTH;

    QPainterPath sinePath;
    sinePath.moveTo(dU, centerV);

    for (float u = 0; u < boundingRect.width(); u += step)
    {
        float t = (u / boundingRect.width()) * WAVE_FREQUENCY;
        float scaleT = runningTime * bpm / 60;

        float amplitude = (WAVE_SWING / 2) * sin(M_PI * 2 * t) * sin(M_PI * 2 * scaleT);

        sinePath.lineTo(u + dU, centerV * (1 + amplitude));
    }

    painter->drawPath(sinePath);
}
