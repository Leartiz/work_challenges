#ifndef DSOMETHING_H
#define DSOMETHING_H

#include <iostream>

class DSomething final
{
public:
    DSomething();
    ~DSomething();
    void add(const int) const;
    void wrt(std::ostream&) const;

private:
    struct D *d{ nullptr };
};

#endif // DSOMETHING_H
