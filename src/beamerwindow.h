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

#include <QQuickView>

class BeamerWindow : public QQuickView
{
    Q_OBJECT
public:
    explicit BeamerWindow(QWindow *parent = 0);
    explicit BeamerWindow(const QUrl& source, QWindow* parent = 0);

    bool initialize();

signals:

public slots:
    void onDimmerChanged(qreal newValue);
    void onPanChanged(qreal newValue);
    void onTiltChanged(qreal newValue);
    void onZoomChanged(qreal newValue);
    void onShutterChanged(bool newValue);
    void onAngleChanged(qreal newValue);

protected:
    QQuickItem* surface;
};
