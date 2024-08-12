#ifndef CONCTWIDGET_H
#define CONCTWIDGET_H

#include <memory>

#include <QWidget>

#include "db/strategy_conct/strategyconct.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ConctWidget; }
QT_END_NAMESPACE

class ConctWidget : public QWidget {
    Q_OBJECT

public:
    explicit ConctWidget(QWidget* parent = nullptr);
    ~ConctWidget() override;

public:
    std::shared_ptr<StrategyConct> getStrategyConct();

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event) override;

signals:
    void closedConctWidget();
    void closedConctWidgetOk();

private slots:
    void chooseConct();

    void on_pushButtonOk_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::ConctWidget *m_ui;
};

#endif // CONCTWIDGET_H
