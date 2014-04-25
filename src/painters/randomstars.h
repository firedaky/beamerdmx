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

#pragma once

#include "laserpainter.h"

class RandomStarsPainter : public LaserPainter
{
    Q_OBJECT
public:
    explicit RandomStarsPainter(QObject *parent);
    RandomStarsPainter(QObject *parent, int stars);
    RandomStarsPainter(QColor color, QObject* parent, int stars);

    virtual void paint(QPainter* painter, QRectF boundingRect);

signals:

public slots:

protected:
    int stars;
    qreal lastDraw;
};
