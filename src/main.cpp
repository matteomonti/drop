#ifdef __main__

#include <iostream>
#include <type_traits>

#include "bytewise/macros.h"
#include "bytewise/buffer.h"
#include "bytewise/scanners/buffer.h"

class yetanotherclass
{
    // Self

    typedef yetanotherclass self;

    // Members

    const bytewise :: buffer m;

    // Bytewise

    bytewise(m);
};

class myotherclass
{
    // Self

    typedef myotherclass self;

    // Members

    double a;
    bytewise :: buffer b;
    const bytewise :: buffer c[10];
    yetanotherclass d;

    // Bytewise

    bytewise(a);
    bytewise(b);
    bytewise(c);
    bytewise(d);
};

class myclass
{
    // Self

    typedef myclass self;

    // Members

    int x;
    myotherclass y;
    bytewise :: buffer z;

    // Bytewise

    bytewise(x);
    bytewise(y);
    bytewise(z);
};

int main()
{
    using namespace bytewise;

    std :: cout << std :: is_same <typename scanners :: buffer <myclass> :: type, map <path <1, 1>, path <1, 2>, path <1, 3, 0>, path <2>>> :: value << std :: endl;
}

#endif
