#pragma once

#include "service/service.h"

namespace lez
{
	namespace service
	{
		namespace impl
		{
			class Math : public contract::Math
			{
			public:
				double calculate_expression(const std::string&) override;
				~Math() override {};
			};
		}
	}
}
