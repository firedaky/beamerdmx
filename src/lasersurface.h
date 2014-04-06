#ifndef LASERSURFACE_H
#define LASERSURFACE_H

#include <QQuickPaintedItem>

class QPainter;
class LaserPainter;

class LaserSurface : public QQuickPaintedItem
{
    Q_OBJECT
public:
    explicit LaserSurface(QQuickItem *parent = 0);

    virtual void paint(QPainter* painter);

signals:

public slots:
    void setLaserPainter(LaserPainter* newPainter);

protected:
    LaserPainter* laserPainter;

};

#endif // LASERSURFACE_H
