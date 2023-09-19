#include "tst_app.h"

#include "../app/coordconverter.h"

AppTests::AppTests() {}
AppTests::~AppTests() {}

// CoordConverter
// -----------------------------------------------------------------------

void AppTests::test_pointToIndex()
{
    QFETCH(QPoint, point);
    QFETCH(int, rowCount);
    QFETCH(int, colCount);
    QFETCH(int, result);

    const auto index = CoordConverter::pointToIndex(
                point, rowCount, colCount);
    QCOMPARE(index, result);
}

void AppTests::test_pointToIndex_data()
{
    QTest::addColumn<QPoint>("point");
    QTest::addColumn<int>("rowCount");
    QTest::addColumn<int>("colCount");
    QTest::addColumn<int>("result");

    // okk
    {
        QTest::newRow("{3, 3} | 10 5 | 18") << QPoint{ 3, 3 } << 10 << 5 << 18;
        QTest::newRow("{2, 0} | 6 2 | 4") << QPoint{ 2, 0 } << 6 << 2 << 4;
        QTest::newRow("{1, 2} | 3 4 | 6") << QPoint{ 1, 2 } << 3 << 4 << 6;
    }
}

void AppTests::test_indexToPair()
{
    QFETCH(int, index);
    QFETCH(int, rowCount);
    QFETCH(int, colCount);

    using Pair = QPair<int, int>;
    QFETCH(Pair, result);

    const auto pair = CoordConverter::indexToPair(
                index, rowCount, colCount);
    QCOMPARE(pair, result);
}

void AppTests::test_indexToPair_data()
{
    QTest::addColumn<int>("index");
    QTest::addColumn<int>("rowCount");
    QTest::addColumn<int>("colCount");

    using Pair = QPair<int, int>;
    QTest::addColumn<Pair>("result");

    // okk
    {
        QTest::newRow("10 | 5 5 | {2, 0}") << 10 << 5 << 5 << Pair{ 2, 0 };
        QTest::newRow("10 | 2 7 | {1, 3}") << 10 << 2 << 7 << Pair{ 1, 3 };
        QTest::newRow("14 | 7 9 | {1, 5}") << 14 << 7 << 9 << Pair{ 1, 5 };
        QTest::newRow("20 | 4 9 | {2, 2}") << 20 << 4 << 9 << Pair{ 2, 2 };

    }
}

// SceneWithSquares
// -----------------------------------------------------------------------

void AppTests::test_SceneWithSquares_recreate()
{
    // TODO: ?
}

void AppTests::test_SceneWithSquares_recreate_data()
{
    // TODO: ?
}

QTEST_APPLESS_MAIN(AppTests)

