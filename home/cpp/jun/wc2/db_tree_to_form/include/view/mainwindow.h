#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>
#include <functional>

#include <QMainWindow>

#include "view/conctwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override = default;

public:
    // mb first?
    void insertFirst();

    void resizeViewColumnWidth();

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void insertRow();
    void removeRow();
    void insertChild();

private slots:
    void cancelSelection();
    void updateStatsBar();
    void updateActions();
    void updateView();

private slots:
    void showMsgDatabaseNotOpened();
    void showConctWidget();

    void takeControl();
    void changeConnection();

private:
    using CstmDltr = std::function<void(Ui::MainWindow*)>;
    std::unique_ptr<Ui::MainWindow, CstmDltr> m_ui;

    // has strategy cont!
    std::unique_ptr<ConctWidget> m_conctWidget;
};

#endif // MAINWINDOW_H
