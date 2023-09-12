#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "scenewithsquares.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void onClicked_pushBtnGenerate();

private:
    Ui::MainWindow *m_ui;
    SceneWithSquares *m_scene;
};

#endif // MAINWINDOW_H
