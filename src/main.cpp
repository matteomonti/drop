#ifdef __main__

#include <iostream>
#include <type_traits>

#include "bytewise/macros.h"
#include "bytewise/scanners/arithmetic.h"

class myotherclass
{
    // Self

    typedef myotherclass self;

    // Members

    int a;
    int b;

    // Bytewise

    bytewise(a);
    bytewise(b);
};

class myclass
{
    // Self

    typedef myclass self;

    // Members

    int x[4];
    double y;
    myotherclass m;
    char q[16];

    // Bytewise

    bytewise(x);
    bytewise(y);
    bytewise(m);
    bytewise(q);
};

int main()
{
    using namespace bytewise;

    std :: cout << std :: is_same
    <
        scanners :: arithmetic <myclass> :: type,
        mask <range <0, 4, true>, range <4, 8, true>, range <8, 12, true>, range <12, 16, true>, range <16, 24, true>, range <24, 28, true>, range <28, 32, true>, range <32, 48, false>>
    > :: value << std :: endl;
}

#endif
