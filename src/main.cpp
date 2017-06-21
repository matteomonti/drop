#ifdef __main__

#include <iostream>
#include <type_traits>

#include "bytewise/macros.h"
#include "bytewise/buffer.h"
#include "bytewise/visitors/buffer.hpp"

struct yetanotherclass
{
    // Self

    typedef yetanotherclass self;

    // Members

    bytewise :: buffer m;

    // Bytewise

    bytewise(m);
};

struct myotherclass
{
    // Self

    typedef myotherclass self;

    // Members

    double a;
    bytewise :: buffer b;
    bytewise :: buffer c[4][4];
    yetanotherclass d;

    // Bytewise

    bytewise(a);
    bytewise(b);
    bytewise(c);
    bytewise(d);
};

struct myclass
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

struct myvisitor
{
    void read(const bytewise :: buffer & data)
    {
        std :: cout << "Received: " << data << std :: endl;
    }
};

int main()
{
    using namespace bytewise;

    myclass myobj;
    myobj.y.b = "myobj.y.b";

    myobj.y.c[0][0] = "myobj.y.c[0][0]";
    myobj.y.c[0][1] = "myobj.y.c[0][1]";
    myobj.y.c[0][2] = "myobj.y.c[0][2]";
    myobj.y.c[0][3] = "myobj.y.c[0][3]";

    myobj.y.c[1][0] = "myobj.y.c[1][0]";
    myobj.y.c[1][1] = "myobj.y.c[1][1]";
    myobj.y.c[1][2] = "myobj.y.c[1][2]";
    myobj.y.c[1][3] = "myobj.y.c[1][3]";

    myobj.y.c[2][0] = "myobj.y.c[2][0]";
    myobj.y.c[2][1] = "myobj.y.c[2][1]";
    myobj.y.c[2][2] = "myobj.y.c[2][2]";
    myobj.y.c[2][3] = "myobj.y.c[2][3]";

    myobj.y.c[3][0] = "myobj.y.c[3][0]";
    myobj.y.c[3][1] = "myobj.y.c[3][1]";
    myobj.y.c[3][2] = "myobj.y.c[3][2]";
    myobj.y.c[3][3] = "myobj.y.c[3][3]";

    myobj.y.d.m = "myobj.y.d.m";
    myobj.z = "myobj.z";

    /*myvisitor visitor;
    visitors :: buffer <myclass> :: read(myobj, visitor);*/

    std :: cout << visitors :: buffer <myclass> :: size(myobj) << std :: endl;
}

#endif
