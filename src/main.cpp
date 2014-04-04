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
#include <QQuickView>
#include <QQmlEngine>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName(BEAMERDMX_NAME);
    a.setApplicationDisplayName(BEAMERDMX_NAME);
    a.setApplicationVersion(BEAMERDMX_VERSION);

    QQuickView mainWindow(QUrl("qrc:/qml/mainwindow.qml"));
    mainWindow.setTitle(a.applicationDisplayName() + " " + a.applicationVersion());
    mainWindow.show();

    QQuickView beamerWindow(QUrl("qrc:/qml/beamerwindow.qml"));
    beamerWindow.setResizeMode(QQuickView::SizeRootObjectToView);
    beamerWindow.show();

    a.connect(dynamic_cast<QObject*>(mainWindow.engine()), SIGNAL(quit()), SLOT(quit()));

    return a.exec();
}
