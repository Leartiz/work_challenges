#include <QDebug>

#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>

#include "db/entities/simpleentity.h"
#include "db/strategy_conct/strategyconctsqlite.h"

const QString StrategyConctSqlite::conctName() const {
    return "qt_default_conct_sqlite";
}

const QString StrategyConctSqlite::driverName() const {
    return "QSQLITE";
}

const QString StrategyConctSqlite::defaultDbName() const {
    return "db_tree_to_form.sqlite";
}

const QString StrategyConctSqlite::lastInsertId() const {
    return "last_insert_rowid()";
}

void StrategyConctSqlite::init() const {
    QSqlDatabase db = QSqlDatabase::addDatabase(driverName(), conctName());
    db.setDatabaseName(defaultDbName());

    if (!db.open()) {
        qCritical() << "StrategyConctSqlite, init, database not open: " << db.lastError();
        return;
    }

    createTbls();

    db.close();
    qInfo() << QString("StrategyConctSqlite init %1 end.").arg(driverName());
}

void StrategyConctSqlite::createSimpleEntity() const {
    const QString sQuery = {
        "CREATE TABLE " + SimpleEntity::Tbl::TblName + " (" +

        SimpleEntity::Tbl::Id + " INTEGER, " +
        SimpleEntity::Tbl::ParentId + " INTEGER, " +
        SimpleEntity::Tbl::Name + " TEXT NOT NULL, " +

        "FOREIGN KEY(" + SimpleEntity::Tbl::ParentId + ") "
        "REFERENCES " + SimpleEntity::Tbl::TblName + "(" + SimpleEntity::Tbl::Id + "), "

        "PRIMARY KEY(" + SimpleEntity::Tbl::Id + ")" +
        ");"
    };
    QSqlQuery query(QSqlDatabase::database(conctName()));
    if (!query.exec(sQuery)) {
        qCritical() << "StrategyConctSqlite, createSimpleEntity, exec failed: " << query.lastError();
        return;
    }
    qInfo() << "Tbl SimpleEntity was created.";
}
