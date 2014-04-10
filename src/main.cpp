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

#include <QApplication>
#include <QDebug>
#include <QQuickView>
#include <QQmlEngine>
#include <QDesktopWidget>

#include "lasercontroller.h"
#include "lasersurface.h"
#include "beamerwindow.h"

int main(int argc, char *argv[])
{
    // Setup RNG
    qsrand(QTime::currentTime().msec());

    // Setup GUI
    QApplication a(argc, argv);
    a.setApplicationName(BEAMERDMX_NAME);
    a.setApplicationDisplayName(BEAMERDMX_NAME);
    a.setApplicationVersion(BEAMERDMX_VERSION);

    qmlRegisterType<LaserSurface>("BeamerDMX", 1, 0, "LaserSurface");

    QQuickView mainWindow(QUrl("qrc:/qml/mainwindow.qml"));
    mainWindow.setTitle(a.applicationDisplayName() + " " + a.applicationVersion());
    mainWindow.setResizeMode(QQuickView::SizeRootObjectToView);
    mainWindow.show();

    BeamerWindow beamerWindow(QUrl("qrc:/qml/beamerwindow.qml"));
    beamerWindow.setResizeMode(QQuickView::SizeRootObjectToView);
    beamerWindow.show();
    if (!beamerWindow.initialize())
    {
        qCritical() << "Beamer window initialization failed";
        return -1;
    }

    // Initialize laser graphics
    LaserSurface* surface = beamerWindow.rootObject()->findChild<LaserSurface*>("LaserSurface");
    if (!surface)
    {
        qCritical() << "Could not find laser surface";
        return -1;
    }

    LaserController controller;
    if (!controller.initialize(surface))
    {
        qCritical() << "Could not initialize laser controller";
        return -1;
    }

    // Setup controls data and connections
    a.connect(dynamic_cast<QObject*>(mainWindow.engine()), SIGNAL(quit()), SLOT(quit()));

    QObject::connect(mainWindow.rootObject(), SIGNAL(showLaserNormal()), &beamerWindow, SLOT(showNormal()));
    QObject::connect(mainWindow.rootObject(), SIGNAL(showLaserFullscreen()), &beamerWindow, SLOT(showFullScreen()));

    QQuickItem* fader;

    // Setup dimmer
    fader = mainWindow.rootObject()->findChild<QQuickItem*>("FaderDimmer");
    if (fader)
    {
        QObject::connect(fader, SIGNAL(faderMoved(qreal)), &controller, SLOT(onDimmerChanged(qreal)));
        fader->setProperty("faderValue", 255);
    }
    else
    {
        qCritical() << "Could not find dimmer fader";
        return -1;
    }

    // Setup pan
    fader = mainWindow.rootObject()->findChild<QQuickItem*>("FaderPan");
    if (fader)
    {
        QObject::connect(fader, SIGNAL(faderMoved(qreal)), &controller, SLOT(onPanCoarseChanged(qreal)));
        fader->setProperty("faderValue", 128);
    }
    else
    {
        qCritical() << "Could not find pan fader";
        return -1;
    }

    fader = mainWindow.rootObject()->findChild<QQuickItem*>("FaderPanFine");
    if (fader)
    {
        QObject::connect(fader, SIGNAL(faderMoved(qreal)), &controller, SLOT(onPanFineChanged(qreal)));
        fader->setProperty("faderValue", 0);
    }
    else
    {
        qCritical() << "Could not find pan fine fader";
        return -1;
    }

    // Setup tilt
    fader = mainWindow.rootObject()->findChild<QQuickItem*>("FaderTilt");
    if (fader)
    {
        QObject::connect(fader, SIGNAL(faderMoved(qreal)), &controller, SLOT(onTiltCoarseChanged(qreal)));
        fader->setProperty("faderValue", 128);
    }
    else
    {
        qCritical() << "Could not find tilt fader";
        return -1;
    }

    fader = mainWindow.rootObject()->findChild<QQuickItem*>("FaderTiltFine");
    if (fader)
    {
        QObject::connect(fader, SIGNAL(faderMoved(qreal)), &controller, SLOT(onTiltFineChanged(qreal)));
        fader->setProperty("faderValue", 0);
    }
    else
    {
        qCritical() << "Could not find tilt fine fader";
        return -1;
    }

    // Setup zoom
    fader = mainWindow.rootObject()->findChild<QQuickItem*>("FaderZoom");
    if (fader)
    {
        QObject::connect(fader, SIGNAL(faderMoved(qreal)), &controller, SLOT(onZoomChanged(qreal)));
        fader->setProperty("faderValue", 255);
    }
    else
    {
        qCritical() << "Could not find zoom fader";
        return -1;
    }

    // Setup strobe/shutter
    fader = mainWindow.rootObject()->findChild<QQuickItem*>("FaderStrobe");
    if (fader)
    {
        QObject::connect(fader, SIGNAL(faderMoved(qreal)), &controller, SLOT(onStrobeChanged(qreal)));
        fader->setProperty("faderValue", 255);
    }
    else
    {
        qCritical() << "Could not find zoom fader";
        return -1;
    }

    // Setup rotation
    fader = mainWindow.rootObject()->findChild<QQuickItem*>("FaderRotation");
    if (fader)
    {
        QObject::connect(fader, SIGNAL(faderMoved(qreal)), &controller, SLOT(onRotationCoarseChanged(qreal)));
        fader->setProperty("faderValue", 128);
    }
    else
    {
        qCritical() << "Could not find rotation fader";
        return -1;
    }

    fader = mainWindow.rootObject()->findChild<QQuickItem*>("FaderRotationFine");
    if (fader)
    {
        QObject::connect(fader, SIGNAL(faderMoved(qreal)), &controller, SLOT(onRotationFineChanged(qreal)));
        fader->setProperty("faderValue", 0);
    }
    else
    {
        qCritical() << "Could not find rotation fine fader";
        return -1;
    }

    // Setup colors
    fader = mainWindow.rootObject()->findChild<QQuickItem*>("FaderColor1");
    if (fader)
    {
        QObject::connect(fader, SIGNAL(faderMoved(qreal)), &controller, SLOT(onColor1Changed(qreal)));
        fader->setProperty("faderValue", 0);
    }
    else
    {
        qCritical() << "Could not find color 1 fader";
        return -1;
    }

    fader = mainWindow.rootObject()->findChild<QQuickItem*>("FaderColor2");
    if (fader)
    {
        QObject::connect(fader, SIGNAL(faderMoved(qreal)), &controller, SLOT(onColor2Changed(qreal)));
        fader->setProperty("faderValue", 0);
    }
    else
    {
        qCritical() << "Could not find color 2 fader";
        return -1;
    }

    fader = mainWindow.rootObject()->findChild<QQuickItem*>("FaderRed");
    if (fader)
    {
        QObject::connect(fader, SIGNAL(faderMoved(qreal)), &controller, SLOT(onRedChanged(qreal)));
        fader->setProperty("faderValue", 0);
    }
    else
    {
        qCritical() << "Could not find red fader";
        return -1;
    }

    fader = mainWindow.rootObject()->findChild<QQuickItem*>("FaderGreen");
    if (fader)
    {
        QObject::connect(fader, SIGNAL(faderMoved(qreal)), &controller, SLOT(onGreenChanged(qreal)));
        fader->setProperty("faderValue", 0);
    }
    else
    {
        qCritical() << "Could not find green fader";
        return -1;
    }

    fader = mainWindow.rootObject()->findChild<QQuickItem*>("FaderBlue");
    if (fader)
    {
        QObject::connect(fader, SIGNAL(faderMoved(qreal)), &controller, SLOT(onBlueChanged(qreal)));
        fader->setProperty("faderValue", 0);
    }
    else
    {
        qCritical() << "Could not find blue fader";
        return -1;
    }

    QObject::connect(&controller, SIGNAL(dimmerChanged(qreal)), &beamerWindow, SLOT(onDimmerChanged(qreal)));
    QObject::connect(&controller, SIGNAL(panChanged(qreal)),    &beamerWindow, SLOT(onPanChanged(qreal)));
    QObject::connect(&controller, SIGNAL(tiltChanged(qreal)),   &beamerWindow, SLOT(onTiltChanged(qreal)));
    QObject::connect(&controller, SIGNAL(zoomChanged(qreal)),   &beamerWindow, SLOT(onZoomChanged(qreal)));
    QObject::connect(&controller, SIGNAL(shutterChanged(bool)), &beamerWindow, SLOT(onShutterChanged(bool)));
    QObject::connect(&controller, SIGNAL(angleChanged(qreal)),  &beamerWindow, SLOT(onAngleChanged(qreal)));

    return a.exec();
}
