#ifdef __main__

#include <iostream>
#include <type_traits>

#include "bytewise/macros.h"
#include "bytewise/scanners/arithmetic.h"

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
    using namespace bytewise;
}

#endif
