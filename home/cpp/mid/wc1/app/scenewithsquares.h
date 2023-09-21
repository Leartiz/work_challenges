#ifndef SCENEWITHSQUARES_H
#define SCENEWITHSQUARES_H

#include <QObject>
#include <QVector>
#include <QHash>

#include <QColor>
#include <QGraphicsScene>
#include <QGraphicsRectItem>

#include <QFuture>
#include <QAtomicInt>

#include <QMutex>
#include <QMutexLocker>

class SquareItem;

class SceneWithSquares : public QGraphicsScene
{
    Q_OBJECT

    friend class AppTests;

private:
    using Row = QVector<SquareItem*>;
    using Matrix = QVector<Row>;
    using Path = QVector<int>;

    struct PathFindingRes final // for future.
    {
        int stateId{ 0 };
        Path path;
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
    void setAutoFindPath(const bool value);

public:
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
    QVector<QVector<int>> toAdjacencyMatrix();
    void recreate(const int w, const int h);
    void block(const int percent = 25);

private:
    QFuture<PathFindingRes> runPathFindingTask(
            const int begVx, const int endVx);
    void reshowPath(const QVector<int>& vec);
    void hideShowedPath();

    // to pimpl?
private:
    Matrix m_rects;
    Row m_begAndEnd;

private:
    Path m_showedPath;
    QHash<QPair<int, int>, Path> m_cachedPaths;
    QVector<QVector<int>> m_cachedAdjMatrix;
    bool m_autoFindPath;
    int m_stateId;
};

#endif // SCENEWITHSQUARES_H
