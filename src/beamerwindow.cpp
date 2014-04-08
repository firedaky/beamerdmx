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

#include <QQuickItem>
#include <QDebug>

#include "beamerwindow.h"

BeamerWindow::BeamerWindow(QWindow *parent) :
    QQuickView(parent),
    surface(nullptr)
{
}

BeamerWindow::BeamerWindow(const QUrl &source, QWindow *parent) :
    QQuickView(source, parent),
    surface(nullptr)
{
}

bool BeamerWindow::initialize()
{
    surface = rootObject()->findChild<QQuickItem*>("LaserSurface");

    if (!surface)
    {
        qCritical() << "Could not find laser surface";

        return false;
    }

    return true;
}

void BeamerWindow::onDimmerChanged(qreal newValue)
{
    surface->setProperty("dimmer", newValue);
}

void BeamerWindow::onPanChanged(qreal newValue)
{
    surface->setProperty("pan", newValue);
}

void BeamerWindow::onTiltChanged(qreal newValue)
{
    surface->setProperty("tilt", newValue);
}

void BeamerWindow::onZoomChanged(qreal newValue)
{
    surface->setProperty("zoom", newValue);
}

void BeamerWindow::onShutterChanged(bool newValue)
{
    surface->setProperty("shutter", newValue);
}
