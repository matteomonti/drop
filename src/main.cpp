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

    // Events

    void on(bytewise :: read)
    {
        std :: cout << "Read event triggered in onelastclass!" << std :: endl;
    }

    void on(bytewise :: write)
    {
        std :: cout << "Write event triggered in onelastclass!" << std :: endl;
    }
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

    // Events

    void on(bytewise :: read)
    {
        std :: cout << "Read event triggered in yetanotherclass!" << std :: endl;
    }

    void on(bytewise :: write)
    {
        std :: cout << "Write event triggered in yetanotherclass!" << std :: endl;
    }
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

    // Events

    void on(bytewise :: read)
    {
        std :: cout << "Read event triggered in myotherclass!" << std :: endl;
    }

    void on(bytewise :: write)
    {
        std :: cout << "Write event triggered in myotherclass!" << std :: endl;
    }
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

    // Events

    void on(bytewise :: read)
    {
        std :: cout << "Read event triggered in myclass!" << std :: endl;
    }

    void on(bytewise :: write)
    {
        std :: cout << "Write event triggered in myclass!" << std :: endl;
    }
};

int main()
{
    myclass myobj;
    auto bytes = bytewise :: serialize(myobj);
    bytewise :: deserialize <myclass> (bytes);
}

#endif
