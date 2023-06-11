#include "handler.h"

namespace lez
{
	namespace delivery
	{
		namespace tcp
		{
			handler::handler(service::contract::math& ms)
				: math_service{ ms } {}
		}
	}
}