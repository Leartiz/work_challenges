#include <string>
#include <sstream>
#include <stdexcept>

#include <lua.hpp>

#include "service/impl/lua_math.h"

namespace lez
{
	namespace service
	{
		namespace impl
		{
            namespace
            {

            void validate_expression(const std::string& expression)
            {
                const size_t new_line_pos = expression.find('\n');
                const size_t semicolon_pos = expression.find(';');

                if (new_line_pos != std::string::npos || semicolon_pos != std::string::npos)
                    throw std::runtime_error{ "invalid character found" };
            }

            } // <anonymous>

            // -----------------------------------------------------------

            Lua_math::Lua_math()
                : m_lua_state{ luaL_newstate() }
            {
                if (!m_lua_state)
                    throw std::runtime_error{ "failed to create lua state" };

                luaL_openlibs(m_lua_state);
            }

            Lua_math::~Lua_math()
            {
                lua_close(m_lua_state);
            }

            double Lua_math::calculate_expression(const std::string& expression)
			{
                validate_expression(expression);

                const std::string lua_code = "result = " + expression;
                if (luaL_dostring(m_lua_state, lua_code.c_str()) != LUA_OK) {
                    std::ostringstream sout;
                    sout << "lua code execution failed with error: " <<
                        lua_tostring(m_lua_state, -1);
                    lua_pop(m_lua_state, 1); // !
                    throw std::runtime_error{ sout.str() };
                }

                lua_getglobal(m_lua_state, "result");
                if (lua_isnumber(m_lua_state, -1)) {
                    const double result = lua_tonumber(m_lua_state, -1); // ok!
                    lua_pop(m_lua_state, 1);
                    return result;
                }

                lua_pop(m_lua_state, 1);
                throw std::runtime_error{ "result is not a number" };
			}
		}
	}
}
