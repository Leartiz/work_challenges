#include <stdexcept>

#include <QtNumeric>
#include <QRandomGenerator>
#include <QDateTime>

#include <QDebug>
#include <QGraphicsSceneMouseEvent>

#include <QtConcurrent/QtConcurrent>

#include "pathfinder.h"
#include "squareitem.h"
#include "scenewithsquares.h"
#include "coordconverter.h"

namespace
{

QVector<QPoint> genRandPoints(const int count,
                              const int w, const int h)
{
    static QRandomGenerator rg(
        quint32(QDateTime::currentDateTimeUtc()
                    .toSecsSinceEpoch())
        );

    // ***

    if (w < 0 || h < 0)
        return {};

    QVector<QPoint> res;
    res.reserve(count);
    for (int i = 0; i < count; ++i) {
        res.push_back(QPoint{
            rg.bounded(0, w), // col
            rg.bounded(0, h)  // row
        });
    }
    return res;
}

bool isObstacleCell(const SquareItem* const one)
{
    return
        one->brush().color() == SceneWithSquares::obstacleCellColor;
}

// not the best solution since...
void putCoordToCell(SquareItem* const square, const QPoint& p)
{
    square->setProperty("coord", p);
}
QPoint getCoordFromCell(const SquareItem* const square)
{
    return square->property("coord").toPoint();
}

int getIndexFromCell(const SquareItem* const square,
                     const int rowCount, const int colCount)
{
    const auto coord =
            getCoordFromCell(
                square);

    // ***

    return CoordConverter::pointToIndex(
                coord, rowCount, colCount);
}

} // <anonymous>

// -----------------------------------------------------------------------

const QColor SceneWithSquares::pathCellColor{ Qt::red };
const QColor SceneWithSquares::freeCellColor{ Qt::lightGray };
const QColor SceneWithSquares::obstacleCellColor{ Qt::black };
const QColor SceneWithSquares::borderCellColor{ Qt::black };

// -----------------------------------------------------------------------

SceneWithSquares::SceneWithSquares(
    const QRectF &sceneRect, QObject *parent)
    : QGraphicsScene{ sceneRect, parent }
    , m_autoFindPath{ true }
    , m_stateId{ 0 }
{}

void SceneWithSquares::setAutoFindPath(const bool value)
{
    m_autoFindPath = value;
    if (m_autoFindPath) {
        return;
    }

    hideShowedPath();
    m_cachedPaths.clear();
}

/* sync */
void SceneWithSquares::generate(const int w, const int h,
                                const int blockedPercent)
{
    if (w <= 0 || h <= 0) {
        throw std::runtime_error(
            QObject::tr("size is incorrect")
                .toStdString());
    }

    if (blockedPercent < 0 || blockedPercent > 100) {
        throw std::runtime_error(
            QObject::tr("percent is incorrect")
                .toStdString());
    }

    // ***

    ++m_stateId;

    recreate(w, h);
    block(blockedPercent);
}

void SceneWithSquares::recreate(const int w, const int h)
{
    clear();
    m_rects.clear();
    m_begAndEnd.clear();

    m_showedPath.clear();
    m_cachedPaths.clear();
    m_cachedAdjMatrix.clear();

    m_rects = Matrix{
        h, Row{ w, nullptr }
    };

    // ***

    const auto sqSideW = sceneRect().width() / w;
    const auto sqSideH = sceneRect().height() / h;

    qreal x = 0, y = 0;
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            const auto square = new SquareItem(
                { x, y, sqSideW, sqSideH });

            {
                const auto ok = connect(square, &SquareItem::clicked,
                                        this, &SceneWithSquares::onClicked_square);
                Q_ASSERT(ok);
            }

            square->setPen(QPen{ borderCellColor });
            square->setBrush(QBrush{ freeCellColor });
            putCoordToCell(square, QPoint{ i, j });

            m_rects[i][j] = square;
            addItem(square);

            x += sqSideW;
        }
        y += sqSideH;
        x = 0;
    }
}

void SceneWithSquares::block(const int percent)
{
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
                ->setBrush(QBrush{ obstacleCellColor });
    }
}

// -----------------------------------------------------------------------

QVector<QVector<int>> SceneWithSquares::toAdjacencyMatrix()
{
    if (!m_cachedAdjMatrix.isEmpty())
        return m_cachedAdjMatrix;

    const auto vxCount = (rowCount() * colCount());
    auto result = QVector<QVector<int>>(
        vxCount, QVector<int>(vxCount, 0));

    // ***

    const auto addEdgeIfNeed =
            [&](
            const int baseI, const int baseJ,
            const int nextI, const int nextJ
            ) -> void {

        if (baseI < 0 || baseI >= rowCount()) return;
        if (baseJ < 0 || baseJ >= colCount()) return;

        if (nextI < 0 || nextI >= rowCount()) return;        
        if (nextJ < 0 || nextJ >= colCount()) return;

        // ***

        const int baseVxIdx =
                CoordConverter::pointToIndex(
                    { baseI, baseJ }, rowCount(), colCount());
        const int nextVxIdx =
                CoordConverter::pointToIndex(
                    { nextI, nextJ }, rowCount(), colCount());

        const auto baseVx = m_rects[baseI][baseJ];
        const auto nextVx = m_rects[nextI][nextJ];

        if (isObstacleCell(baseVx)) return;
        if (isObstacleCell(nextVx)) return;

        // ***

        result[baseVxIdx][nextVxIdx] = 1;
        result[nextVxIdx][baseVxIdx] = 1;
    };

    // ***

    for (int i = 0; i < rowCount(); ++i) {
        for (int j = 0; j < colCount(); ++j) {
            // neighbors...
            addEdgeIfNeed(i, j, i + 1, j);
            addEdgeIfNeed(i, j, i - 1, j);
            addEdgeIfNeed(i, j, i, j + 1);
            addEdgeIfNeed(i, j, i, j - 1);
        }
    }

    m_cachedAdjMatrix = result; // cow!
    return m_cachedAdjMatrix;
}

int SceneWithSquares::rowCount() const
{
    return m_rects.size();
}

int SceneWithSquares::colCount() const
{
    if (m_rects.empty())
        return 0;

    return m_rects[0].size();
}

// -----------------------------------------------------------------------

void SceneWithSquares::mouseMoveEvent(
    QGraphicsSceneMouseEvent* event)
{
    if (!m_autoFindPath) return;
    if (m_begAndEnd.size() != 1) return;

    hideShowedPath();

    auto const item = itemAt(event->lastScenePos(), {});
    auto const square = dynamic_cast<SquareItem*>(item);

    if (!square) return;
    if (isObstacleCell(square)) return;

    // ***

    const QPair<int, int> begAndEndVxs{
        getIndexFromCell(m_begAndEnd[0], rowCount(), colCount()),
        getIndexFromCell(square, rowCount(), colCount())
    };

    if (m_cachedPaths.contains(begAndEndVxs)) {
        reshowPath(m_cachedPaths[begAndEndVxs]);
        return;
    }

    // ***

    const auto future = runPathFindingTask(
        begAndEndVxs.first, begAndEndVxs.second
        );

    const auto fw = new QFutureWatcher<PathFindingRes>(this);
    fw->setFuture(future);

    // ***

    const auto ok = connect(fw, &QFutureWatcher<QVector<int>>::finished,
                            this, [this, begAndEndVxs]() -> void {
        const auto fw = static_cast<QFutureWatcher<PathFindingRes>*>(sender());
        const auto future = fw->future();
        const auto futResult = future.result();

        if (futResult.stateId != m_stateId) {
            return;
        }
        if (!m_autoFindPath) {
            return;
        }

        // ***

        m_cachedPaths[begAndEndVxs] = futResult.path;
        reshowPath(futResult.path);
        fw->deleteLater();
    });

    Q_ASSERT(ok);
}

void SceneWithSquares::onClicked_square()
{
    if (m_begAndEnd.size() >= 2)
        return;

    const auto square =
        qobject_cast<SquareItem*>(
                sender());

    if (isObstacleCell(square))
        return;

    if (m_begAndEnd.size() == 1) {
        if (m_begAndEnd.front() == square) {
            return;
        }
    }

    // ***

    if (m_begAndEnd.empty()) {
        square->setText("A");
    }
    else {
        square->setText("B");
    }

    // ***

    m_begAndEnd.push_back(square);
    square->setBrush(
                QBrush{ pathCellColor }
                );

    // ***

    if (m_begAndEnd.size() == 2) {
        const auto future = runPathFindingTask(
            getIndexFromCell(m_begAndEnd[0], rowCount(), colCount()),
            getIndexFromCell(m_begAndEnd[1], rowCount(), colCount())
            );

        const auto fw = new QFutureWatcher<PathFindingRes>(this);
        fw->setFuture(future);

        const auto ok = connect(fw, &QFutureWatcher<QVector<int>>::finished,
                                this, [this]() -> void {
            const auto fw = static_cast<QFutureWatcher<PathFindingRes>*>(sender());
            const auto future = fw->future();
            const auto futResult = future.result();

            if (futResult.stateId != m_stateId) {
                return;
            }

            if (futResult.path.empty()) {
                emit pathNotFound();
            }

            reshowPath(futResult.path);
            m_cachedPaths.clear();
            fw->deleteLater();
        });

        Q_ASSERT(ok);
    }
}

QFuture<SceneWithSquares::PathFindingRes> SceneWithSquares::runPathFindingTask(
        const int begVx, const int endVx)
{
    return QtConcurrent::run(
                [](
                const int stateId,
                const int beg, const int end,
                QVector<QVector<int>> mx
                ) -> PathFindingRes {

        const PathFinder pathFinder{ std::move(mx) };
        return { stateId, pathFinder.get(beg, end) };

    },
        m_stateId, begVx, endVx,
        toAdjacencyMatrix()); // copy or move? cow!
}

// -----------------------------------------------------------------------

void SceneWithSquares::reshowPath(const QVector<int>& vec)
{
    hideShowedPath();

    m_showedPath = vec;
    for (int i = 0; i < vec.size(); ++i) {
        const auto coord =
                CoordConverter::indexToPair(
                    vec[i], rowCount(), colCount());

        m_rects[coord.first][coord.second]
                ->setBrush(QBrush{ pathCellColor });
    }
}

void SceneWithSquares::hideShowedPath()
{
    if (m_showedPath.empty()) return;

    for (int i = 0; i < m_showedPath.size(); ++i) {
        const auto coord =
                CoordConverter::indexToPair(
                    m_showedPath[i], rowCount(), colCount());

        if (m_rects[coord.first][coord.second]->brush().color() == pathCellColor)
            m_rects[coord.first][coord.second]
                    ->setBrush(QBrush{ freeCellColor });
    }

    // ***

    if (!m_begAndEnd.empty()) {
        for (int i = 0; i < m_begAndEnd.size(); ++i) {
            m_begAndEnd[i]->setBrush(QBrush{ pathCellColor });
        }
    }

    m_showedPath.clear();
}
