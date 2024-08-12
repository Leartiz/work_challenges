#ifndef DBFACADE_H
#define DBFACADE_H

#include <memory>
#include <optional>

#include <QObject>
#include <QVector>

#include <QSqlDatabase>

#include "db/entities/simpleentity.h"
#include "db/strategy_conct/strategyconct.h"

class DBFacade final {
public:
    static DBFacade& instance();
    ~DBFacade();

public:
    bool hasDb() const;
    bool isOpened() const;
    void changeConct(const StrategyConct& sc);

public:
    static QString qs(const QString& vl);

public:
    QVector<SimpleEntity> selAllSimpleEntities() const;

    void insSimpleEntities(const SimpleEntity& se) const;
    void updSimpleEntityById(const SimpleEntity& se) const;
    void delSimpleEntityById(const int id) const;

    std::optional<int> selLastInsertId() const;

private:
    std::unique_ptr<QSqlDatabase> m_sqlDatabase;

    QString m_lastInsertId;
    QString m_curConctName; // not empty!

private:
    DBFacade() = default;
    Q_DISABLE_COPY(DBFacade)

    void destroy();
};

#endif // DBFACADE_H
