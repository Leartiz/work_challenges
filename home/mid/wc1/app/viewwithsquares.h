#ifndef VIEWWITHSQUARES_H
#define VIEWWITHSQUARES_H

#include <QGraphicsView>
#include <QObject>

class ViewWithSquares : public QGraphicsView
{
    Q_OBJECT

public:
    explicit ViewWithSquares(QWidget *parent = nullptr);
    explicit ViewWithSquares(QGraphicsScene *scene, QWidget *parent = nullptr);

    // QWidget interface
protected:
    void wheelEvent(QWheelEvent *event) override;
};

#endif // VIEWWITHSQUARES_H
