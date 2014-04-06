#include <QPainter>

#include "lasersurface.h"

LaserSurface::LaserSurface(QQuickItem *parent) :
    QQuickPaintedItem(parent),
    laserPainter(nullptr)
{
}

void LaserSurface::paint(QPainter *painter)
{
    if (laserPainter)
    {
        // TODO: Call paint method on LaserPainter.
    }
    else
    {
#ifdef DEBUG
        // In debug builds, we warn about an unset laser painter by turning the screen magenta.
        painter->fillRect(contentsBoundingRect(), Qt::magenta);
#else
        painter->fillRect(contentsBoundingRect(), Qt::black);
#endif
    }
}

void LaserSurface::setLaserPainter(LaserPainter *newPainter)
{
    laserPainter = newPainter;
}
