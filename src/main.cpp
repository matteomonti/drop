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

    // Static methods

    void on(bytewise :: read) const
    {
        std :: cout << "onelastclass read" << std :: endl;
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

    // Static methods

    void on(bytewise :: read) const
    {
        std :: cout << "yetanotherclass read" << std :: endl;
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

    // Static methods

    void on(bytewise :: read) const
    {
        std :: cout << "myotherclass read" << std :: endl;
    }
};

class myclass
{
public:

    // Self

    typedef myclass self;

    // Constructors

    myclass()
    {
    }

    // Members

    int x;
    myotherclass m[10];
    onelastclass o;

    // Bytewise

    bytewise(x);
    bytewise(m);
    bytewise(o);

    // Static methods

    void on(bytewise :: read) const
    {
        std :: cout << "myclass read" << std :: endl;
    }
};

int main()
{
    myclass myobj;
    auto bytes = bytewise :: serialize(myobj);
    std :: cout << bytes.size() << std :: endl;
}

#endif
