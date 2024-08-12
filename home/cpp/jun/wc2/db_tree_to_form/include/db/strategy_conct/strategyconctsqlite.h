#ifndef STRATEGYCONCTSQLITE_H
#define STRATEGYCONCTSQLITE_H

#include "db/strategy_conct/strategyconct.h"

class StrategyConctSqlite : public StrategyConct {
    // StrategyConct interface
protected:
    const QString conctName() const override;
    const QString driverName() const override;
    const QString defaultDbName() const override;

protected:
    const QString lastInsertId() const override;

protected:
    void init() const override;
    void createSimpleEntity() const override;
};

#endif // STRATEGYCONCTSQLITE_H
