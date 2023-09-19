#ifndef SQUAREITEM_H
#define SQUAREITEM_H

#include <QObject>
#include <QGraphicsRectItem>

class SquareItem : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

public:
    explicit SquareItem(const QRectF &rect);

signals:
    void clicked();
    void hovered();

    // QGraphicsItem interface
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent*);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*);    
};

#endif // SQUAREITEM_H
