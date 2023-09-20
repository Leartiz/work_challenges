#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QSettings>
#include <QMainWindow>

#include "scenewithsquares.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    struct ConfigKey final
    {
        static const char* winPos;
    };

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    // QWidget interface
protected:
    void wheelEvent(QWheelEvent *event) override;
    void moveEvent(QMoveEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

private slots:
    void onClicked_pushBtnGenerate();
    void onTriggered_actionAutoFindPath();
    void onPathNotFound_scene();

private:
    Ui::MainWindow *m_ui;
    SceneWithSquares *m_scene;
    QSettings* m_settings;
};

#endif // MAINWINDOW_H
