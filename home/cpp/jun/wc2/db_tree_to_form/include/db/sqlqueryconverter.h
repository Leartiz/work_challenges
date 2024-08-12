#ifndef SQLQUERYCONVERTER_H
#define SQLQUERYCONVERTER_H

#include <QVector>
#include <QSqlQuery>

#include "db/entities/simpleentity.h"

class SqlQueryConverter final {
public:
    static QVector<SimpleEntity> queryToSimpleEntities(QSqlQuery& query);
};

#endif // SQLQUERYCONVERTER_H
