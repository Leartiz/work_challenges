#include <string>
#include <cassert>
#include <stdexcept>
#include <iostream>

#include "exprtk.hpp"

double calc(const std::string& expr_string)
{
    using namespace exprtk;

    parser<double> pars;
    expression<double> expr;

    if (!pars.compile(expr_string, expr))
        throw std::runtime_error("calc, compile failed");
    return expr.value();
}

int main()
{
    try {
        assert(calc("5+5") == 10); std::cout << ".";
        assert(calc("5*2+sqrt(4)") == 12); std::cout << ".";
        assert(calc("1/2*3") == 1.5); std::cout << ".";
    }
    catch (std::exception& e) {
        std::cerr << "er: " << e.what() << std::endl;
    }

    // ***

    std::cout << "\n[OK]" << std::endl;
    return 0;
}
