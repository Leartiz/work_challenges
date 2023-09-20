#include <QWheelEvent>

#include "viewwithsquares.h"

ViewWithSquares::ViewWithSquares(QWidget *parent)
    : QGraphicsView{ parent } {}

ViewWithSquares::ViewWithSquares(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView{ scene, parent } {}

void ViewWithSquares::wheelEvent(QWheelEvent *event)
{
    event->ignore();
}
