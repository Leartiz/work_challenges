#include <any>
#include <string>
#include <sstream>
#include <memory>
#include <format>

#include <QDebug>

#include <lua.hpp>
#include <boost/lexical_cast.hpp>

#include "tst_common.h"

#include "service/math_service.h"
#include "service/impl/lua_math.h"

#include "adapters/interfaces/tcp/dto/math/payload_with_expr.h"
#include "adapters/interfaces/tcp/dto/request.h"

#include "nlohmann/json.hpp"

Q_DECLARE_METATYPE(std::string)

// -----------------------------------------------------------------------

Common::Common() {}
Common::~Common() {}

// Lua Math Service!
// -----------------------------------------------------------------------

void Common::test_Lua_math_calculate_expression_n0()
{
    using namespace lez::service::contract;
    using namespace lez::service::impl;

    std::shared_ptr<Math_service> m = std::make_shared<Lua_math>();
    QCOMPARE(m->calculate_expression("5+5"), 10);
}

void Common::test_Lua_math_calculate_expression_n1()
{
    using namespace lez::service::contract;
    using namespace lez::service::impl;

    std::shared_ptr<Math_service> m = std::make_shared<Lua_math>();
    QCOMPARE(m->calculate_expression("5*5*3"), 75);
}

// -----------------------------------------------------------------------

void Common::test_Lua_math_calculate_expression_err_n0()
{
    using namespace lez::service::contract;
    using namespace lez::service::impl;

    std::shared_ptr<Math_service> m = std::make_shared<Lua_math>();
    QVERIFY_THROWS_EXCEPTION(std::runtime_error,
                             (m->calculate_expression("5 5 5 5")));

    //QVERIFY_THROWS_NO_EXCEPTION((m->calculate_expression("5 5 5 5")));
}

void Common::test_Lua_math_calculate_expression_err_n1()
{
    using namespace lez::service::contract;
    using namespace lez::service::impl;

    std::shared_ptr<Math_service> m = std::make_shared<Lua_math>();
    QVERIFY_THROWS_EXCEPTION(std::runtime_error,
                             (m->calculate_expression("5+5; while true do end")));
}

// -----------------------------------------------------------------------

void Common::test_Lua_math_calculate_expression_data()
{
    QTest::addColumn<std::string>("expression");
    QTest::addColumn<double>("result");

    {
        const double result = 5;
        const std::string expression = "2+3";
        QTest::newRow(expression.c_str()) << expression << result;
    }
    {
        const double result = 22;
        const std::string expression = "11*2";
        QTest::newRow(expression.c_str()) << expression << result;
    }
    //...
}

void Common::test_Lua_math_calculate_expression()
{
    QFETCH(std::string, expression);
    QFETCH(double, result);

    // ***

    using namespace lez::service::contract;
    using namespace lez::service::impl;

    std::shared_ptr<Math_service> m = std::make_shared<Lua_math>();
    QCOMPARE(m->calculate_expression(expression), result);
}

// -----------------------------------------------------------------------

void Common::test_Payload_with_expr_to_json_n0()
{
    using nlohmann::json;
    using namespace lez::adapters::interfaces::tcp::dto;

    math::Payload_with_expr pd;
    pd.set_expr("1 + 2 + 3 + 4 + 5");
    const auto j = pd.to_json();

    std::ostringstream sout; sout << j;
    qDebug() << sout.str();
}

void Common::test_Payload_with_expr_from_json_n0()
{
    using nlohmann::json;
    using namespace lez::adapters::interfaces::tcp::dto;

    const std::string expr = "1 + 2 + 3 + 4 + 5";

    math::Payload_with_expr pd;
    const json j = {
        { "payload", {
              { "expression", expr.c_str() }
          } }
    };
    pd.from_json(j);

    QCOMPARE_EQ(pd.get_expr(), expr);
}

// -----------------------------------------------------------------------

void Common::test_Request_to_json_n0()
{
    using namespace lez::adapters::interfaces::tcp::dto;
    Request r;
    const auto j = r.to_json();
    std::ostringstream sout; sout << j;
    qDebug() << sout.str();
}

// std library
// -----------------------------------------------------------------------

void Common::test_std_any_to_string()
{
    std::any a = std::string("any string");
    std::ostringstream sout;
    sout << std::any_cast<std::string>(a);
    qDebug() << sout.str();
}

void Common::test_std_format()
{
    qDebug() << std::format("missing `{}` in JSON",
                            std::string("test_key")).c_str();
}

// experiments with some dependencies
// -----------------------------------------------------------------------

void Common::test_lua_calculate_expression()
{
    lua_State* lua_state = luaL_newstate();
    luaL_openlibs(lua_state);

    // ***

    const std::string expression = "3 * (4 + 5) - 2 / 1";
    const std::string lua_code = "result = " + expression;

    if (luaL_dostring(lua_state, lua_code.c_str()) != LUA_OK) {
        std::ostringstream sout;
        sout << "Lua error: " << lua_tostring(lua_state, -1);
        lua_pop(lua_state, 1);
        lua_close(lua_state);

        QFAIL(sout.str().c_str());
    }

    // ***

    lua_getglobal(lua_state, "result");
    if (lua_isnumber(lua_state, -1)) {
        double result = lua_tonumber(lua_state, -1);
        qDebug() << "Result: " << result << '\n'; // !

    } else {
        QFAIL( "Error: result is not a number!");
    }

    lua_pop(lua_state, 1);
    lua_close(lua_state); // !
}

// -----------------------------------------------------------------------

void Common::test_nlohmann_json()
{
    nlohmann::json ex = nlohmann::json::parse(R"(
        {
            "pi": 3.141,
            "happy": true
        }
    )");

    const int pi_val = ex["pi"];
    const bool happy_val = ex["happy"];

    qDebug() << "pi_val:" << pi_val;
    qDebug() << "happy_val:" << happy_val;
}

// -----------------------------------------------------------------------

void Common::test_boost_lexical_cast_data()
{
    QTest::addColumn<std::string>("input");
    QTest::addColumn<bool>("expected");

    // ***

    QTest::newRow("true 1") << std::string("1") << true;
    QTest::newRow("false 0") << std::string("0") << false;

    /*
        QTest::newRow("true") << std::string("true") << true;
        QTest::newRow("false") << std::string("false") << false;
    */
}

void Common::test_boost_lexical_cast()
{
    QFETCH(std::string, input);
    QFETCH(bool, expected);

    QCOMPARE(boost::lexical_cast<bool>(input), expected);
}

QTEST_APPLESS_MAIN(Common)
