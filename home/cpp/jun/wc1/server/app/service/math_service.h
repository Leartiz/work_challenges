#pragma once

#include <string>

namespace lez
{
	namespace service
	{
		namespace contract
		{
            class Math_service
			{
			public:
				virtual double calculate_expression(const std::string&) = 0;
                virtual ~Math_service() {};
			};
		}
	}
}

