#ifndef TST_APP_H
#define TST_APP_H

#include <QtTest>

class AppTests : public QObject
{
    Q_OBJECT

public:
    AppTests();
    ~AppTests();

private slots:
    void test_pointToIndex();
    void test_pointToIndex_data();

    void test_indexToPair();
    void test_indexToPair_data();

private slots:
    void test_SceneWithSquares_recreate();
    void test_SceneWithSquares_recreate_data();

private slots:
    void test_PathFinder_get();
    void test_PathFinder_get_data();
};


#endif // TST_APP_H
