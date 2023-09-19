#include <QBrush>
#include <QPainter>

#include <QDebug>
#include <QApplication>

#include <QFont>
#include <QFontMetrics>

#include "squareitem.h"

SquareItem::SquareItem(const QRectF &rect)
    : QGraphicsRectItem{ rect } {}

void SquareItem::setText(const QString& txt)
{
    m_text = txt;
}

void SquareItem::mousePressEvent(QGraphicsSceneMouseEvent*)
{}

void SquareItem::mouseReleaseEvent(QGraphicsSceneMouseEvent*)
{
    emit clicked();
}

void SquareItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                       QWidget *widget)
{
    QGraphicsRectItem::paint(painter, option, widget);

    const auto fontSize = qRound(
        std::min(
            rect().width(),
            rect().height())
        / 1.5);

    const QFont font{ "Helvetica", fontSize };
    const QFontMetrics fontMetrics(font);
    const auto textRect =
        fontMetrics.boundingRect(m_text);

    const QPointF pos = QPointF(
        rect().x() + (rect().width() / 2 - textRect.width() / 1.9),
        rect().y() + (rect().height() / 2 + textRect.height() / 3.2)
        );

    painter->setFont(font);
    painter->drawText(
        pos, m_text);
}
