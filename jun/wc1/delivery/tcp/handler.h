#pragma once

#include "service/service.h"

namespace lez
{
	namespace delivery
	{
		namespace tcp
		{
			class handler
			{
			public:
				handler(service::contract::math&);
				virtual ~handler() {};

				// Reqs
			public:
				double calc_expr(const std::string& body);

			private:
				service::contract::math& math_service;
			};
		}
	}
}