#include <QIcon>
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
    setWindowIcon(
        QIcon(":/logo/res/maze.png"));

    // ***

    {
        connect(m_ui->pushBtnGenerate, &QPushButton::clicked,
                this, &MainWindow::onClicked_pushBtnGenerate);
    }

    // ***

    m_scene = new SceneWithSquares(
        { 0, 0, 500, 500 });

    m_ui->graphicsView->setScene(m_scene);
    m_ui->graphicsView
        ->setMouseTracking(true);
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::onClicked_pushBtnGenerate()
{
    m_scene->recreate(
        m_ui->spinBoxW->value(),
        m_ui->spinBoxH->value());

    // ***

    m_scene->block();

    // ***

    m_scene->advance();
}
