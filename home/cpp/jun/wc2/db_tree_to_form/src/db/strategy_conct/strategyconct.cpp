#include <QStringList>

#include <QSqlDatabase>

#include "db/entities/simpleentity.h"
#include "db/strategy_conct/strategyconct.h"

void StrategyConct::createTbls() const {
    QSqlDatabase sqlDatabase = QSqlDatabase::database(conctName()); // open!
    const auto tables = sqlDatabase.tables();
    if (!tables.contains(SimpleEntity::Tbl::TblName))
        createSimpleEntity(); // heir!
}
