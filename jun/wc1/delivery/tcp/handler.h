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
				handler(service::math&);
				virtual ~handler() {};

			public:
				// Reqs

			private:
				service::math& math_service;
			};
		}
	}
}