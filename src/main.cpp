#ifdef __main__

#include <iostream>
#include <type_traits>
#include <string>
#include <iomanip>

#include "bytewise/macros.h"
#include "bytewise/serialize.hpp"
#include "bytewise/deserialize.hpp"
#include "bytewise/visitors/on.hpp"

class onelastclass
{
public:

    // Self

    typedef onelastclass self;

    // Members

    int w;

    // Bytewise

    bytewise(w);
};

class yetanotherclass
{
public:

    // Self

    typedef yetanotherclass self;

    // Members

    int z;

    // Bytewise

    bytewise(z);
};

class myotherclass
{
public:

    // Self

    typedef myotherclass self;

    // Members

    int y;
    double h[14];
    yetanotherclass n[2];
    yetanotherclass * q;

    // Bytewise

    bytewise(y);
    bytewise(h);
    bytewise(n);
    bytewise(q);
};

class myclass
{
public:

    // Self

    typedef myclass self;

    // Members

    int x;
    myotherclass m[10];
    onelastclass o;

    // Bytewise

    bytewise(x);
    bytewise(m);
    bytewise(o);
};

int main()
{
    myclass myobj;
    auto bytes = bytewise :: serialize(myobj);
    std :: cout << bytes.size() << std :: endl;
}

#endif
