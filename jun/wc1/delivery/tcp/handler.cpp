#include "handler.h"

namespace lez
{
	namespace delivery
	{
		namespace tcp
		{
			handler::handler(service::contract::math& ms)
				: math_service{ ms } {}

			double handler::calc_expr(const std::string& body)
			{
				math_service.calc_expr
			}
		}
	}
}