#include <QDebug>

#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>

#include "db/entities/simpleentity.h"
#include "db/strategy_conct/strategyconctmysql.h"

StrategyConctMySql::StrategyConctMySql(const QString& dbName)
    : dbName(dbName) {}

const QString StrategyConctMySql::conctName() const {
    return "qt_default_conct_mysql";
}

const QString StrategyConctMySql::driverName() const {
    return "QMYSQL";
}

const QString StrategyConctMySql::defaultDbName() const {
    return "test_db";
}

const QString StrategyConctMySql::lastInsertId() const {
    return "last_insert_id()";
}

void StrategyConctMySql::init() const {
    auto sqlDatabase = QSqlDatabase::addDatabase(driverName(), conctName());
    sqlDatabase.setDatabaseName(dbName);
    sqlDatabase.setHostName(hostname);

    sqlDatabase.setUserName(username);
    sqlDatabase.setPassword(password);

    if (!sqlDatabase.open()) {
        qCritical() << "StrategyConctMySql, init, database not open: " << sqlDatabase.lastError();
        return;
    }

    createTbls();

    sqlDatabase.close();
    qInfo() << QString("StrategyConctMySql init %1 end.").arg(driverName());
}

void StrategyConctMySql::createTbls() const {
    const QString sQuery = {
        "SHOW TABLES;"
    };
    QSqlQuery query(QSqlDatabase::database(conctName()));
    if (!query.exec(sQuery)) {
        qCritical() << "StrategyConctMySql, createTbls, exec failed: " << query.lastError();
        return;
    }

    QStringList tables;
    while (query.next())
        tables.append(query.value(0).toString()); // table name!

    if (!tables.contains(SimpleEntity::Tbl::TblName, Qt::CaseInsensitive))
        createSimpleEntity();
}

void StrategyConctMySql::createSimpleEntity() const {
    const QString sQuery = {
        "CREATE TABLE " + SimpleEntity::Tbl::TblName + " (" +

        SimpleEntity::Tbl::Id + " INTEGER AUTO_INCREMENT, " +
        SimpleEntity::Tbl::ParentId + " INTEGER, " +
        SimpleEntity::Tbl::Name + " VARCHAR(255) NOT NULL, " +

        "FOREIGN KEY(" + SimpleEntity::Tbl::ParentId + ") "
        "REFERENCES " + SimpleEntity::Tbl::TblName + "(" + SimpleEntity::Tbl::Tbl::Id + "), "

        "PRIMARY KEY(" + SimpleEntity::Tbl::Id + ")" +
        ");"
    };
    QSqlQuery query(QSqlDatabase::database(conctName()));
    if (!query.exec(sQuery)) {
        qCritical() << "StrategyConctMySql, createSimpleEntity, exec failed: " << query.lastError();
        return;
    }
    qInfo() << "Tbl SimpleEntity was created.";
}
