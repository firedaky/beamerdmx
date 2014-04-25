//   Copyright 2014 Daniel Kucher

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

#include "randomstars.h"
#include "../colors.h"

#define STD_COLOR Colors::White

static const int STD_STARS = 10;
static std::vector<QPoint> starArray;

RandomStarsPainter::RandomStarsPainter(QObject *parent) :
    LaserPainter(parent), stars(STD_STARS), lastDraw(0)
{
    primaryColor = STD_COLOR;
}

RandomStarsPainter::RandomStarsPainter(QObject *parent, int stars) :
    LaserPainter(parent), stars(stars), lastDraw(0)
{
    primaryColor = STD_COLOR;
}

RandomStarsPainter::RandomStarsPainter(QColor color, QObject *parent, int stars) :
    LaserPainter(parent), stars(stars), lastDraw(0)
{
    primaryColor = color;
}

void RandomStarsPainter::paint(QPainter *painter, QRectF boundingRect)
{
    if(bpm / 60 < (runningTime - lastDraw)) {
        lastDraw = runningTime;

        int width = boundingRect.width();
        int height = boundingRect.height();

        int tempLocX, tempLocY;

        starArray.resize(stars);

        for(int i = 0; i < stars; i++) {

            tempLocX = qrand() * width / RAND_MAX;
            tempLocY = qrand() * height / RAND_MAX;
            starArray[i] = QPoint(tempLocX, tempLocY);
        }
    }

    for(int i = 0; i < starArray.size(); i++) {
        QColor color = overridePrimary ? primaryOverrideColor : primaryColor;
        // QPen pen(color, DEFAULT_LINE_THICKNESS, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

        QBrush brush(color);

        painter->setRenderHint(QPainter::Antialiasing, true);
        painter->setBrush(brush);
        painter->drawEllipse(starArray[i], 5, 5);
    }
}
