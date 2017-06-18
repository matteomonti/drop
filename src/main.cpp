#ifdef __main__

#include <iostream>
#include <type_traits>

#include "bytewise/macros.h"
#include "bytewise/proxy.hpp"

class myclass
{
    // Self

    typedef myclass self;

    // Members

    int x;
    double y;
    char z;

    // Bytewise

    bytewise(x);
    bytewise(y);
    bytewise(z);
};

int main()
{
    myclass myobj;

    bytewise :: proxy <myclass, 0> :: get(myobj) = 17;
    std :: cout << bytewise :: proxy <myclass, 0> :: get(myobj) << std :: endl;
}

#endif
