#include <QIcon>

#include <QDebug>
#include <QMessageBox>

#include <QWheelEvent>
#include <QScrollBar>
#include <QtMath>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
    setWindowIcon(
        QIcon(":/logo/res/maze.png"));

    m_scene = new SceneWithSquares(
        { 0, 0, 500, 500 });

    // ***

    // ui
    {
        auto ok = connect(m_ui->pushBtnGenerate, &QPushButton::clicked,
                          this, &MainWindow::onClicked_pushBtnGenerate);
        Q_ASSERT(ok);
    }

    // model
    {
        auto ok = connect(m_scene, &SceneWithSquares::pathNotFound,
                          this, &MainWindow::onPathNotFound_scene);
        Q_ASSERT(ok);
    }

    m_ui->graphicsView->setScene(m_scene);
    m_ui->graphicsView
        ->setMouseTracking(true);

    // ***

    m_ui->graphicsView->verticalScrollBar()->blockSignals(true);
    m_ui->graphicsView->horizontalScrollBar()->blockSignals(true);

    m_ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::wheelEvent(QWheelEvent *pWheelEvent)
{
    /*
    qDebug() << "angleDelta:" << pWheelEvent->angleDelta();
    qDebug() << "pixelDelta:" << pWheelEvent->pixelDelta();

    qDebug() << "phase:"    << pWheelEvent->phase();
    qDebug() << "position:" << pWheelEvent->position();

    qDebug() << "viewport width:" << m_ui->graphicsView->viewport()->width();
    qDebug() << "viewport height" << m_ui->graphicsView->viewport()->height();
    */

    // ***

    const double angle = pWheelEvent->angleDelta().y(); // 120, -120
    const double factor = qPow(1.00075, angle); /* manual selection */

    const QPointF targetViewportPos = pWheelEvent->position();
    const QPointF targetScenePos = m_ui->graphicsView->mapToScene(
        targetViewportPos.toPoint());

    m_ui->graphicsView->scale(factor, factor);
    m_ui->graphicsView->centerOn(targetScenePos);

    const QPointF viewportCenterPos{
        m_ui->graphicsView->viewport()->width() / 2.0,
        m_ui->graphicsView->viewport()->height() / 2.0
    };
    const QPointF deltaViewportPos =
        targetScenePos - viewportCenterPos;

    const QPointF viewportCenter =
        m_ui->graphicsView->mapFromScene(targetScenePos) -
                                   deltaViewportPos;
    m_ui->graphicsView->centerOn(
        m_ui->graphicsView->mapToScene(
            viewportCenter.toPoint()));

    return;
}

void MainWindow::onClicked_pushBtnGenerate()
{
    m_scene->generate(
                m_ui->spinBoxW->value(),
                m_ui->spinBoxH->value()
                );

    // ***

    m_ui->graphicsView->resetTransform();
    m_scene->advance();
}

void MainWindow::onPathNotFound_scene()
{
    QMessageBox::information(this, tr("Info"), tr("Path not found!"));
}
