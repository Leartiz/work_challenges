#include <QBrush>
#include <QDebug>
#include <QApplication>

#include "squareitem.h"

SquareItem::SquareItem(const QRectF &rect)
    : QGraphicsRectItem{ rect } {}

void SquareItem::mousePressEvent(QGraphicsSceneMouseEvent*)
{}

void SquareItem::mouseReleaseEvent(QGraphicsSceneMouseEvent*)
{
    emit clicked();
}
