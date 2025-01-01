#pragma once

#include <string>
#include <memory>

namespace lez
{
	namespace service
	{
		namespace contract
		{            
            class Math_service
			{
            public:
                static constexpr char SERVICE_NAME[] = "math";

                struct Action final
                {
                    static constexpr char CALCULATE[] = "calculate";
                    //...
                };

			public:
				virtual double calculate_expression(const std::string&) = 0;
                virtual ~Math_service() {};
			};

            using Sp_math_service = \
                std::shared_ptr<Math_service>;
		}
	}
}

