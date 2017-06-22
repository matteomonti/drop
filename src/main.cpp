#ifdef __main__

#include <iostream>
#include <type_traits>
#include <string>
#include <iomanip>

#include "bytewise/macros.h"
#include "bytewise/serialize.hpp"

class myclass
{
public:

    // Self

    typedef myclass self;

    // Members

    bytewise :: buffer w;

    int x;
    double y;
    char z[4];

    // Bytewise

    bytewise(w);

    bytewise(x);
    bytewise(y);
    bytewise(z);
};

int main()
{
    myclass myobj;
    myobj.w = "Hello, world!";
    myobj.x = 3;
    myobj.y = 4.5;

    myobj.z[0] = 6;
    myobj.z[1] = 7;
    myobj.z[2] = 8;
    myobj.z[3] = 9;

    auto bytes = bytewise :: serialize(myobj);
}

#endif
