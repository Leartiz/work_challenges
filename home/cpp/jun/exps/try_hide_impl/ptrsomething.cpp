#include <vector>

#include "ptrsomething.h"

using namespace std;

namespace
{

std::vector<int>* vals{ nullptr };

}

// -----------------------------------------------------------------------

PtrSomething::PtrSomething(){
    vals = new std::vector<int>();
}

PtrSomething::~PtrSomething(){
    auto tmp = vals;
    vals = nullptr;
    delete tmp;
}

void PtrSomething::add(const int val) const{
    if (vals) {
        vals->push_back(val);
        return;
    }
    cout << "vals is nullptr" << endl;
}

void PtrSomething::wrt(std::ostream& out) const{
    if (vals) {
        for (auto it = vals->begin(); it != vals->end(); ++it)
            out << *it << " ";
        return;
    }
    cout << "vals is nullptr" << endl;
}
