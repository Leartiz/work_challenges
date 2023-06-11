#include <stdexcept>

#include <exprtk.hpp>

#include "math.h"

namespace lez
{
	namespace service
	{
		namespace impl
		{
			double math::calc_expr(const std::string& expr_string)
			{
				using namespace exprtk;

				parser<double> parser;
				expression<double> expr;

				if (!parser.compile(expr_string, expr))
				{
					printf("Compilation error...\n");
					return;
				}

				return expr.value();
			}
		}
	}
}