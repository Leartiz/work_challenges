#include <vector>

#include "valsomething.h"

using namespace std;

namespace
{

struct Bundle final
{
    static std::vector<int>& vals() {
        static std::vector<int> one;
        return one;
    }
};

}

// -----------------------------------------------------------------------

ValSomething::ValSomething(){
    Bundle::vals().clear();
}

void ValSomething::add(const int val) const {
    Bundle::vals().push_back(val);
}

void ValSomething::wrt(std::ostream& out) const {
    const auto& vals = Bundle::vals();
    for (auto it = vals.begin(); it != vals.end(); ++it) {
        out << *it << " ";
    }
}
