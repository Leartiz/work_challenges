#ifndef VALSOMETHING_H
#define VALSOMETHING_H

#include <iostream>

class ValSomething final
{
public:
    ValSomething();
    void add(const int) const;
    void wrt(std::ostream&) const;
};

#endif // VALSOMETHING_H
