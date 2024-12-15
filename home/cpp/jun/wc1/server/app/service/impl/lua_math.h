#pragma once

#include <lua.hpp>

#include "service/math_service.h"

namespace lez
{
	namespace service
	{
		namespace impl
		{
            class Lua_math : public contract::Math_service
			{
			public:
                Lua_math();

            public:
				double calculate_expression(const std::string&) override;
                ~Lua_math() override;

            private:
                lua_State* m_lua_state;
			};
		}
	}
}
