#ifndef SQUAREITEM_H
#define SQUAREITEM_H

#include <QObject>
#include <QGraphicsRectItem>

class SquareItem : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

public:
    explicit SquareItem(const QRectF &rect);
    void setText(const QString& txt);

signals:
    void clicked();
    void hovered();

    // QGraphicsItem interface
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent*);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*);

    // QGraphicsItem interface
public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

private:
    QString m_text;
};

#endif // SQUAREITEM_H
