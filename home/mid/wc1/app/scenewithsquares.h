#ifndef SCENEWITHSQUARES_H
#define SCENEWITHSQUARES_H

#include <QColor>
#include <QObject>
#include <QVector>

#include <QGraphicsScene>
#include <QGraphicsRectItem>

class SceneWithSquares : public QGraphicsScene
{
    Q_OBJECT

public:
    static const QColor freeCellColor;
    static const QColor obstacleCellColor;
    static const QColor begOrEndCellColor;
    static const QColor borderCellColor;

public:
    explicit SceneWithSquares(
        const QRectF &sceneRect,
        QObject *parent = nullptr);
    void recreate(int w, int h);
    void block(int percent = 25);

public:
    QVector<QVector<int>> toAdjacencyMatrix();
    int rowCount() const;
    int colCount() const;

    // QGraphicsScene interface
protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent*);

private slots:
    void onClicked_square();

private:
    using Row = QVector<QGraphicsRectItem*>;
    using Matrix = QVector<Row>;
    Matrix m_rects;
    Row m_begAndEnd;

private:
    qreal m_squareSideW{ 0 };
    qreal m_squareSideH{ 0 };
};

#endif // SCENEWITHSQUARES_H
