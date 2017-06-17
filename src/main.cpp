#ifdef __main__

#include <iostream>

#include "bytewise/macros.h"

class myclass
{
    // Self

    typedef myclass self;

public:

    // Members

    int n;
    double k;

    bytewise(n);
    bytewise(k);
};

int main()
{
    myclass myobj;

    myobj.n = 33;
    std :: cout << myclass :: bytewise <0, false> :: get(myobj) << std :: endl;

    myclass :: bytewise <1, false> :: get(myobj) = 4.56;
    std :: cout << myobj.k << std :: endl;
}

#endif
