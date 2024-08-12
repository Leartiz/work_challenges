#include <QIcon>
#include <QWidget>
#include <QResizeEvent>
#include <QMessageBox>

#include "ui_mainwindow.h"
#include "view/mainwindow.h"
#include "model/treemodel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(std::make_unique<Ui::MainWindow>())
    , m_conctWidget(std::make_unique<ConctWidget>()) {
    m_ui.get_deleter() = std::default_delete<Ui::MainWindow>();
    m_ui->setupUi(this);
    resizeViewColumnWidth();

    TreeModel* treeModel = new TreeModel(this);
    m_ui->treeView->setModel(treeModel);
    changeConnection(); // set first sqlite!

    {
        connect(m_ui->actionExit, &QAction::triggered, qApp, &QCoreApplication::quit);

        auto sm = m_ui->treeView->selectionModel();
        connect(sm, &QItemSelectionModel::selectionChanged, this, &MainWindow::updateStatsBar);
        connect(sm, &QItemSelectionModel::selectionChanged, this, &MainWindow::updateActions);
        updateActions();
    }

    {
        connect(treeModel, &TreeModel::databaseNotOpened, this, &MainWindow::showMsgDatabaseNotOpened);
        connect(m_ui->actionChgConct, &QAction::triggered, this, &MainWindow::showConctWidget);

        connect(m_conctWidget.get(), &ConctWidget::closedConctWidget, this, &MainWindow::takeControl);
        connect(m_conctWidget.get(), &ConctWidget::closedConctWidgetOk, this, &MainWindow::changeConnection);
    }

    connect(m_ui->actionAddRow, &QAction::triggered, this, &MainWindow::insertRow);
    connect(m_ui->actionRmvRow, &QAction::triggered, this, &MainWindow::removeRow);
    connect(m_ui->actionAddChild, &QAction::triggered, this, &MainWindow::insertChild);

    connect(m_ui->actionUpdView, &QAction::triggered, this, &MainWindow::updateView);
    connect(m_ui->actionCancelSelection, &QAction::triggered, this, &MainWindow::cancelSelection);
}

void MainWindow::showMsgDatabaseNotOpened() {
    QMessageBox msgBox;
    msgBox.setWindowTitle("Ошибка");
    msgBox.setWindowIcon(windowIcon());
    msgBox.setText("Не подключен к БД!");
    msgBox.setIcon(QMessageBox::Icon::Warning);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}

void MainWindow::insertFirst() {
    QAbstractItemModel* model = m_ui->treeView->model();
    model->insertRow(0);
}

void MainWindow::insertRow() {
    const QModelIndex index = m_ui->treeView->selectionModel()->currentIndex();
    if (!index.isValid()) {
        insertFirst();
        return;
    }

    QAbstractItemModel* model = m_ui->treeView->model();
    if (model->insertRow(index.row() + 1, index.parent())) {
        m_ui->statusBar->showMessage("insertRow OK!");
        return;
    }
    m_ui->statusBar->showMessage("insertRow FAIL!");
}

void MainWindow::removeRow() {
    const QModelIndex index = m_ui->treeView->selectionModel()->currentIndex();
    if (!index.isValid())
        return;

    QAbstractItemModel* model = m_ui->treeView->model();
    if (model->removeRow(index.row(), index.parent())) {
        m_ui->statusBar->showMessage("removeRow OK!");
        return;
    }
    m_ui->statusBar->showMessage("removeRow FAIL!");
}

void MainWindow::insertChild() {
    const QModelIndex index = m_ui->treeView->selectionModel()->currentIndex();
    if (!index.isValid()) {
        insertFirst();
        return;
    }

    QAbstractItemModel* model = m_ui->treeView->model();
    if (model->insertRow(0, index)) { // sub root!
        m_ui->statusBar->showMessage("insertChild OK!");
        return;
    }
    m_ui->statusBar->showMessage("insertChild FAIL!");
}

void MainWindow::cancelSelection() {
    m_ui->treeView->selectionModel()->clearSelection();
    m_ui->statusBar->showMessage("No selected TreeItem! Default top TreeItem!");
}

void MainWindow::updateStatsBar() {
    m_ui->statusBar->showMessage("");
    const bool hasCurrent = m_ui->treeView->selectionModel()->hasSelection();
    if (hasCurrent) {
        if (!m_ui->treeView->selectionModel()->currentIndex().isValid())
            return;

        const int row = m_ui->treeView->selectionModel()->currentIndex().row();
        const int col = m_ui->treeView->selectionModel()->currentIndex().column();

        if (m_ui->treeView->selectionModel()->currentIndex().parent().isValid()) {
            m_ui->statusBar->showMessage(tr("TreeItem: (%1, %2)").arg(row).arg(col));
            return;
        }
        m_ui->statusBar->showMessage(tr("Top TreeItem: (%1, %2)").arg(row).arg(col));
        return;
    }
}

void MainWindow::updateActions() {
    const bool hasCurrent = m_ui->treeView->selectionModel()->hasSelection();
    m_ui->actionRmvRow->setEnabled(hasCurrent);
}

void MainWindow::updateView() {
    cancelSelection();
    static_cast<TreeModel*>(m_ui->treeView->model())->reloadTreeItemsFromDb();
}

void MainWindow::showConctWidget() {
    setEnabled(false);
    m_conctWidget->show();
}

void MainWindow::takeControl() {
    setEnabled(true);
}

void MainWindow::changeConnection() {
    auto treeModel = static_cast<TreeModel*>(m_ui->treeView->model());
    auto strategyConct = m_conctWidget->getStrategyConct();
    treeModel->changeDatabaseConct(*strategyConct); // tmp!
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    resizeViewColumnWidth();
    event->setAccepted(true);
}

void MainWindow::resizeViewColumnWidth() {
    QTreeView* treeView = m_ui->treeView;
    treeView->setColumnWidth(0, width() / 2 - 50); // rnd off x!
}
