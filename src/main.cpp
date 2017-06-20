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
    const int * c;

    // Bytewise

    //bytewise(a);
    //bytewise(b);
    bytewise(c);
};

class myclass
{
    // Self

    typedef myclass self;

    // Members

    int x[4];
    double y;
    const myotherclass m;
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
    std :: cout << scanners :: arithmetic <myclass> :: writable << std :: endl;
}

#endif
