#include <QCloseEvent>
#include <QRadioButton>

#include "view/conctwidget.h"
#include "ui_conctwidget.h"

#include "db/strategy_conct/strategyconctmysql.h"
#include "db/strategy_conct/strategyconctsqlite.h"

ConctWidget::ConctWidget(QWidget* parent)
    : QWidget(parent), m_ui(new Ui::ConctWidget) {
    m_ui->setupUi(this);

    m_ui->radioBtnSQLite->setChecked(true);
    m_ui->groupBoxSttgsMySql->setEnabled(false);

    connect(m_ui->radioBtnSQLite, &QRadioButton::toggled, this, &ConctWidget::chooseConct);
}

ConctWidget::~ConctWidget() {
    delete m_ui;
}

std::shared_ptr<StrategyConct> ConctWidget::getStrategyConct() {
    if (m_ui->radioBtnSQLite->isChecked()) {
        return std::make_shared<StrategyConctSqlite>(); // basic!
    }

    auto scMySql = std::make_shared<StrategyConctMySql>();
    scMySql->hostname = m_ui->lineEditHostName->text();
    scMySql->dbName = m_ui->lineEditDbName->text();

    scMySql->username = m_ui->lineEditUsrnm->text();
    scMySql->password = m_ui->lineEditPsswrd->text();
    return scMySql;
}

void ConctWidget::chooseConct() {
    QRadioButton* radioBtnSQLite = m_ui->radioBtnSQLite;
    m_ui->groupBoxSttgsMySql->setEnabled(!radioBtnSQLite->isChecked());
}

void ConctWidget::closeEvent(QCloseEvent *event) {
    emit closedConctWidget();
    event->setAccepted(true);
}

void ConctWidget::on_pushButtonOk_clicked() {
    emit closedConctWidgetOk();
    close();
}

void ConctWidget::on_pushButtonCancel_clicked() {
    close();
}
