#include <stdexcept>

#include <exprtk.hpp>

#include "service/impl/math.h"

namespace lez
{
	namespace service
	{
		namespace impl
		{
			double math::calc_expr(const std::string& expr_string) /* wrap */
			{
				using namespace exprtk;

				parser<double> pars;
				expression<double> expr;

				if (!pars.compile(expr_string, expr))
					throw std::runtime_error("math, calc_expr, compile er");
				return expr.value();
			}
		}
	}
}