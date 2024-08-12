#include <utility> // move!

#include <QVariant>
#include <QSqlRecord>

#include "db/sqlqueryconverter.h"

QVector<SimpleEntity> SqlQueryConverter::queryToSimpleEntities(QSqlQuery& query) {
    const QSqlRecord rec = query.record();
    const int idIx = rec.indexOf(SimpleEntity::Tbl::Id);
    const int parentIdIx = rec.indexOf(SimpleEntity::Tbl::ParentId);
    const int nameIx = rec.indexOf(SimpleEntity::Tbl::Name);

    QVector<SimpleEntity> vec;
    while (query.next()) {
        SimpleEntity se(query.value(idIx).toInt());
        if (!query.value(parentIdIx).isNull())
            se.setParentId(query.value(parentIdIx).toInt());

        se.setName(query.value(nameIx).toString());
        vec.append(std::move(se));
    }
    return vec;
}
