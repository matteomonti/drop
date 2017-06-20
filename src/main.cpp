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

    bytewise :: buffer m;

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
    const bytewise :: buffer ** c[10];
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

    std :: cout << scanners :: buffer <myclass> :: writable << std :: endl;
}

#endif
