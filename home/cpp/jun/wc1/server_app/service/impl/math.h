#pragma once

#include "service/service.h"

namespace lez
{
	namespace service
	{
		namespace impl
		{
			struct math : contract::math
			{
				double calc_expr(const std::string&) override;
				~math() override {};
			};
		}
	}
}


