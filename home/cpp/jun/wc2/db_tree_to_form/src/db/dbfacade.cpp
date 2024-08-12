#include <QDebug>

#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>

#include "db/dbfacade.h"
#include "db/sqlqueryconverter.h"

#include "db/strategy_conct/strategyconctmysql.h"
#include "db/strategy_conct/strategyconctsqlite.h"

DBFacade& DBFacade::instance() {
    static DBFacade dbFacade;
    return dbFacade;
}

bool DBFacade::hasDb() const {
    return static_cast<bool>(m_sqlDatabase);
}

bool DBFacade::isOpened() const {
    if (!hasDb()) return false;
    return m_sqlDatabase->isOpen();
}

void DBFacade::changeConct(const StrategyConct& sc) {
    if (QSqlDatabase::contains(sc.conctName())) return;
    destroy();

    m_curConctName = sc.conctName();
    m_lastInsertId = sc.lastInsertId();

    sc.init();
    // permanent opened!
    m_sqlDatabase = std::make_unique<QSqlDatabase>(QSqlDatabase::database(m_curConctName));
}

QString DBFacade::qs(const QString& vl) {
    return "'" + vl + "'";
}

QVector<SimpleEntity> DBFacade::selAllSimpleEntities() const {
    if (!isOpened()) return {}; // or has db?

    // SELECT * FROM table_name;
    const QString sQuery = {
        "SELECT * FROM " + SimpleEntity::Tbl::TblName + ";"
    };
    QSqlQuery query(*m_sqlDatabase);
    if (!query.exec(sQuery)) {
        qCritical() << "DBFacade, selAllSimpleEntities, exec failed: " << query.lastError() << ".";
        qCritical() << "Last query: " << query.lastQuery() << ".";
        return {};
    }
    return SqlQueryConverter::queryToSimpleEntities(query);
}

void DBFacade::insSimpleEntities(const SimpleEntity& se) const {
    if (!isOpened()) return;

    // INSERT INTO table (column1, column2, ...)
    // VALUES (value1, value2 , ...), (value1, value2 , ...), (value1, value2 , ...), ...;
    const QString sParentId = se.getParentId().has_value() ? QString::number(se.getParentId().value()) : "NULL";
    const QString sQuery = {
        "INSERT INTO " + SimpleEntity::Tbl::TblName + " (" +
        SimpleEntity::Tbl::Name + ", " + SimpleEntity::Tbl::ParentId + ") " +
        "VALUES (" + qs(se.getName()) + ", " + sParentId + ");"
    };
    QSqlQuery query(*m_sqlDatabase);
    if (!query.exec(sQuery)) {
        qCritical() << "DBFacade, insSimpleEntities, exec failed: " << query.lastError() << ".";
        qCritical() << "Last query: " << query.lastQuery() << ".";
    }
}

void DBFacade::updSimpleEntityById(const SimpleEntity& se) const {
    if (!isOpened()) return;

    // UPDATE table SET col1 = nwval1, col2 = nwval2, ... WHERE colN == valN;
    if (!se.getId().has_value())
        return;

    const QString sQuery = {
        "UPDATE " + SimpleEntity::Tbl::TblName + " SET " +
        SimpleEntity::Tbl::Name + " = " + qs(se.getName()) + " WHERE " +
        SimpleEntity::Tbl::Id + " = " + QString::number(se.getId().value())
    };
    QSqlQuery query(*m_sqlDatabase);
    if (!query.exec(sQuery)) {
        qCritical() << "DBFacade, updSimpleEntityById, exec failed: " << query.lastError() << ".";
        qCritical() << "Last query: " << query.lastQuery() << ".";
    }
}

void DBFacade::delSimpleEntityById(const int id) const {
    if (!isOpened()) return;

    // DELETE FROM table WHERE condWhere;
    const QString sQuery = {
        "DELETE FROM " + SimpleEntity::Tbl::TblName + " " +
        "WHERE " + SimpleEntity::Tbl::Id + " = " + QString::number(id) + ";"
    };
    QSqlQuery query(*m_sqlDatabase);
    if (!query.exec(sQuery)) {
        qCritical() << "DBFacade, delSimpleEntityById, exec failed: " << query.lastError() << ".";
        qCritical() << "Last query: " << query.lastQuery() << ".";
    }
}

std::optional<int> DBFacade::selLastInsertId() const {
    if (!isOpened()) return {};

    const QString sQuery = {
        "SELECT " + m_lastInsertId + " ;" // spec func!
    };
    QSqlQuery query(*m_sqlDatabase);
    if (!query.exec(sQuery) || !query.first()) {
        qCritical() << "DBFacade, selLastInsertId, exec failed: " << query.lastError() << ".";
        qCritical() << "Last query: " << query.lastQuery() << ".";
        return {};
    }
    return query.value(m_lastInsertId).toInt();
}

DBFacade::~DBFacade() {
    destroy();
}

void DBFacade::destroy() {
    if (!hasDb()) return;

    m_sqlDatabase->close();
    m_sqlDatabase.reset();
    QSqlDatabase::removeDatabase(m_curConctName);

    m_curConctName.clear();
    m_lastInsertId.clear();
}
