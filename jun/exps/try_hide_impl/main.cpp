#include <iostream>

#include "valsomething.h"
#include "ptrsomething.h"
#include "dsomething.h"

using namespace std;

int main()
{
    // val
    cout << "val:" << endl;
    {
        ValSomething gs0;
        gs0.add(10);
        gs0.wrt(cout);

        cout << endl;
        {
            ValSomething gs1;
            gs1.add(15);
            gs1.wrt(cout);
        }
        cout << endl;
        {
            gs0.add(11);
            gs0.wrt(cout);
        }
    }
    cout << endl;

    // ptr
    cout << "ptr:" << endl;
    {
        PtrSomething ps0;
        ps0.add(10);
        ps0.wrt(cout);

        cout << endl;
        {
            PtrSomething ps1;
            ps1.add(15);
            ps1.wrt(cout);
        }
        cout << endl;
        {
            ps0.add(11);
            ps0.wrt(cout);
        }
    }
    cout << endl;

    // d
    cout << "d:" << endl;
    {
        DSomething d0;
        d0.add(10);
        d0.wrt(cout);

        cout << endl;
        {
            DSomething d1;
            d1.add(15);
            d1.wrt(cout);
        }
        cout << endl;
        {
            d0.add(11);
            d0.wrt(cout);
        }
    }
    cout << endl;

    return 0;
}
