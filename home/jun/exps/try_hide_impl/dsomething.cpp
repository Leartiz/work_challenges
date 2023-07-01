#include <vector>

#include "dsomething.h"

using namespace std;

struct D final
{
    std::vector<int> vals;
};

// -----------------------------------------------------------------------

DSomething::DSomething()
    : d{ new D }{}

DSomething::~DSomething(){
    delete d;
}

void DSomething::add(const int val) const
{
    d->vals.push_back(val);
}

void DSomething::wrt(std::ostream& out) const
{
    for (auto it = d->vals.begin(); it != d->vals.end(); ++it) {
        out << *it << " ";
    }
}
