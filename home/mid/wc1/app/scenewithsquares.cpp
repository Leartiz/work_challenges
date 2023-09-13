#include <stdexcept>

#include <QtNumeric>
#include <QRandomGenerator>
#include <QDebug>

#include <QGraphicsSceneMouseEvent>

#include "scenewithsquares.h"
#include "squareitem.h"

namespace
{

QVector<QPoint> genRandPoints(const int count,
                              const int w, const int h)
{
    static QRandomGenerator rg;

    if (w < 0 || h < 0)
        return {};

    QVector<QPoint> res;
    res.reserve(count);
    for (int i = 0; i < count; ++i) {
        res.push_back(QPoint{
            rg.bounded(0, w),
            rg.bounded(0, h)
        });
    }
    return res;
}

} // <anonymous>

// -----------------------------------------------------------------------

SceneWithSquares::SceneWithSquares(
    const QRectF &sceneRect,
    QObject *parent)
    : QGraphicsScene{ sceneRect, parent }
{}

void SceneWithSquares::recreate(int w, int h)
{
    if (w <= 0 || h <= 0) {
        throw std::runtime_error(
            QObject::tr("size is incorrect")
                .toStdString());
    }

    // ***

    clear();
    m_begEnd.clear();
    m_rects = Matrix{
        h, Row{ w, nullptr }
    };

    m_squareSideW = sceneRect().width() / w;
    m_squareSideH = sceneRect().width() / h;

    qreal x = 0, y = 0;
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            const auto square = new SquareItem(
                { x, y, m_squareSideW, m_squareSideH });

            {
                connect(square, &SquareItem::clicked,
                        this, &SceneWithSquares::onClicked_square);
            }

            square->setPen(QPen{ Qt::black });
            square->setBrush(QBrush{ Qt::lightGray });

            m_rects[i][j] = square;
            addItem(square);

            x += m_squareSideW;
        }
        y += m_squareSideH;
        x = 0;
    }
}

void SceneWithSquares::block(int percent)
{
    if (percent < 0 || percent > 100) {
        throw std::runtime_error(
            QObject::tr("percent is incorrect")
                .toStdString());
    }

    if (m_rects.empty()) {
        throw std::runtime_error(
            QObject::tr("rects is empty")
                .toStdString());
    }

    const int w = colCount();
    const int h = rowCount();

    // ***

    const int obstacleCount{
        qRound(w * h * (percent / 100.0))
    };

    const auto points = genRandPoints(
        obstacleCount, w, h);

    for (const auto& p : points) {
        m_rects[p.y()][p.x()]
            ->setBrush(QBrush{ Qt::black });
    }
}

QVector<QVector<int>> SceneWithSquares::toAdjacencyMatrix()
{
    const auto vCount = rowCount() * colCount();
    auto result = QVector<QVector<int>>(
        vCount, QVector<int>(vCount, 0));

    // ***

    for (int i = 0; i < rowCount(); ++i) {
        for (int j = 0; j < colCount(); ++j) {

        }
    }

    return result;
}

int SceneWithSquares::rowCount() const
{
    return m_rects.size();
}

int SceneWithSquares::colCount() const
{
    if (m_rects.empty()) {
        return 0;
    }

    return m_rects[0].size();
}

// -----------------------------------------------------------------------

void SceneWithSquares::mouseMoveEvent(
    QGraphicsSceneMouseEvent* event)
{
    auto item = itemAt(event->lastScenePos(), {});
    auto square = dynamic_cast<SquareItem*>(item);
    if (!square) return;

    QGraphicsScene::mouseMoveEvent(event);
}

void SceneWithSquares::onClicked_square()
{
    if (m_begEnd.size() >= 2)
        return;

    const auto square =
        qobject_cast<SquareItem*>(sender());

    if (m_begEnd.size() == 1) {
        if (m_begEnd.front() == square) {
            return;
        }
    }

    m_begEnd.push_back(square);
    square->setBrush(
        QBrush{ Qt::red });

    // ***

    if (m_begEnd.size() == 2) {

    }
}
