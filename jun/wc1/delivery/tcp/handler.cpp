#include "handler.h"

namespace lez
{
	namespace delivery
	{
		namespace tcp
		{
			handler::handler(service::math& ms)
				: math_service{ ms } {}
		}
	}
}