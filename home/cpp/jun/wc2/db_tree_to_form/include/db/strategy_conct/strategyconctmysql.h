#ifndef STRATEGYCONCTMYSQL_H
#define STRATEGYCONCTMYSQL_H

#include <QString>

#include "db/strategy_conct/strategyconct.h"

class StrategyConctMySql : public StrategyConct {
public:
    StrategyConctMySql() = default;
    explicit StrategyConctMySql(const QString& dbName);

    // StrategyConct interface
protected:
    const QString conctName() const override;
    const QString driverName() const override;
    const QString defaultDbName() const override;

protected:
    const QString lastInsertId() const override;

protected:
    void init() const override;

    void createTbls() const override;
    void createSimpleEntity() const override;

public:
    QString hostname;
    QString dbName;

    QString username;
    QString password;
};

#endif // STRATEGYCONCTMYSQL_H
