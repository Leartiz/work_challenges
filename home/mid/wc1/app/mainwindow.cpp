#include <QIcon>

#include <QDebug>
#include <QMessageBox>

#include <QWheelEvent>
#include <QScrollBar>
#include <QtMath>

#include "mainwindow.h"
#include "ui_mainwindow.h"

const char* MainWindow::ConfigKey::winPos{ "win_pos" };

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

        // actions
        {
            ok = connect(m_ui->actionExit, &QAction::triggered,
                         qApp, &QApplication::quit);
            Q_ASSERT(ok);

            ok = connect(m_ui->actionAutoFindPath, &QAction::triggered,
                         this, &MainWindow::onTriggered_actionAutoFindPath);
            Q_ASSERT(ok);
        }
    }

    // model
    {
        auto ok = connect(m_scene, &SceneWithSquares::pathNotFound,
                          this, &MainWindow::onPathNotFound_scene);
        Q_ASSERT(ok);
    }

    m_ui->graphicsView->setScene(m_scene);
    m_ui->graphicsView->setMouseTracking(true);

    // ***

    m_ui->graphicsView->verticalScrollBar()->blockSignals(true);
    m_ui->graphicsView->horizontalScrollBar()->blockSignals(true);

    m_ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // ***

    m_settings = new QSettings(
        "config.ini", QSettings::Format::IniFormat, this);

    if (m_settings->contains(ConfigKey::winPos)) {
        move(m_settings->value(ConfigKey::winPos).toPoint());
    }
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

// TODO: move the handler to view?
void MainWindow::wheelEvent(QWheelEvent *event)
{    
    const double zoomInFactor = 1.1;
    const double zoomOutFactor = 0.9;

    double zoomFactor = zoomInFactor;
    if (event->angleDelta().y() < 0) {
        zoomFactor = zoomOutFactor;
    }

    const QPointF targetViewportPos =
        event->position();

    // ***

    const QPointF oldScenePos = m_ui->graphicsView->mapToScene(
        targetViewportPos.toPoint());

    m_ui->graphicsView->scale(
        zoomFactor, zoomFactor);

    const QPointF newScenePos = m_ui->graphicsView->mapToScene(
        targetViewportPos.toPoint());

    // ***

    const QPointF deltaViewportPos =
        newScenePos - oldScenePos;

    m_ui->graphicsView->translate(
        deltaViewportPos.x(), deltaViewportPos.y()
        );

    event->accept();
}

void MainWindow::moveEvent(QMoveEvent *event)
{
    QMainWindow::moveEvent(event);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    m_settings->setValue(ConfigKey::winPos, pos());
    event->accept();
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

void MainWindow::onTriggered_actionAutoFindPath()
{
    m_scene->setAutoFindPath(
        m_ui->actionAutoFindPath->isChecked());
}

void MainWindow::onPathNotFound_scene()
{
    QMessageBox::information(
        this, tr("Info"), tr("Path not found!"));
}
