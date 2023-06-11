#pragma once

#include <string>

namespace lez
{
	namespace service
	{
		namespace contract
		{
			struct math
			{
				virtual double calc_expr(const std::string&) = 0;
				virtual ~math() {};
			};
		}
	}
}

