#ifndef STRATEGYCONCT_H
#define STRATEGYCONCT_H

#include <QString>

class StrategyConct {
    friend class DBFacade; // fwd?

public:
    StrategyConct() = default;
    virtual ~StrategyConct() = default;

protected:
    virtual const QString conctName() const = 0;
    virtual const QString driverName() const = 0;
    virtual const QString defaultDbName() const = 0;

protected:
    virtual const QString lastInsertId() const = 0;

protected:
    virtual void init() const = 0;

    virtual void createTbls() const;
    virtual void createSimpleEntity() const = 0;
};

#endif // STRATEGYCONCT_H
