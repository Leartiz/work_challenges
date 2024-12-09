#ifndef TST_COMMON_H
#define TST_COMMON_H

#include <QtTest>

// add necessary includes here

class Common : public QObject
{
    Q_OBJECT

public:
    Common();
    ~Common();

private slots:
    void test_Lua_math_calculate_expression_n0();
    void test_Lua_math_calculate_expression_n1();

    void test_Lua_math_calculate_expression_err_n0();
    void test_Lua_math_calculate_expression_err_n1();

    void test_Lua_math_calculate_expression_data();
    void test_Lua_math_calculate_expression();

public slots:
    void test_std_any_to_string();

    // some dependencies!

private slots:
    void test_lua_calculate_expression();

private slots:
    void test_nlohmann_json();

private slots:
    void test_boost_lexical_cast_data();
    void test_boost_lexical_cast();
};


#endif // TST_COMMON_H
