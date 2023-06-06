#ifndef PTRSOMETHING_H
#define PTRSOMETHING_H

#include <iostream>

class PtrSomething final
{
public:
    PtrSomething();
    ~PtrSomething();
    void add(const int) const;
    void wrt(std::ostream&) const;
};

#endif // PTRSOMETHING_H
