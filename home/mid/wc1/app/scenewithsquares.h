#ifndef SCENEWITHSQUARES_H
#define SCENEWITHSQUARES_H

#include <QObject>
#include <QVector>
#include <QHash>

#include <QColor>
#include <QGraphicsScene>
#include <QGraphicsRectItem>

#include <QFuture>
#include <QUuid>

#include <QMutex>
#include <QMutexLocker>

class SquareItem;

class SceneWithSquares : public QGraphicsScene
{
    Q_OBJECT

    friend class AppTests;

    using Row = QVector<SquareItem*>;
    using Matrix = QVector<Row>;

    struct PathFindingRes final
    {
        QUuid stateId;
        QVector<int> path;
    };

public:
    static const QColor pathCellColor;
    static const QColor freeCellColor;
    static const QColor obstacleCellColor;
    static const QColor borderCellColor;

public:
    explicit SceneWithSquares(
        const QRectF &sceneRect,
        QObject *parent = nullptr);
    void generate(const int w, const int h,
                  const int blockedPercent = 25);

public:
    QVector<QVector<int>> toAdjacencyMatrix();
    int rowCount() const;
    int colCount() const;

signals:
    void pathNotFound();

    // QGraphicsScene interface
protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent*);

private slots:
    void onClicked_square();

private:
    void recreate(const int w, const int h);
    void block(const int percent = 25);

private:
    QFuture<PathFindingRes> runPathFindingTask(
            const int begVx, const int endVx);
    void reshowPath(const QVector<int>& vec);
    void hideShowedPath();

private:
    Matrix m_rects;
    Row m_begAndEnd;

private:
    qreal m_squareSideW{ 0 };
    qreal m_squareSideH{ 0 };

private:
    QRecursiveMutex m_mxShowPath;
    QVector<int> m_showedPath;
    QHash<QPair<int, int>, QVector<int>> m_cachedPaths;
    QUuid m_stateId;
};

#endif // SCENEWITHSQUARES_H
