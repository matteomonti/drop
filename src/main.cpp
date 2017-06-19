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

    std :: cout << std :: is_same <scanners :: arithmetic <myclass> :: repeat <3, 3, mask <range <0, 4, true>>, 4> :: type, mask <range <3, 7, true>, range <7, 11, true>, range <11, 15, true>>> :: value << std :: endl;
    std :: cout << std :: is_same <scanners :: arithmetic <myclass> :: repeat <3, 3, mask <range <0, 2, true>>, 4> :: type, mask <range <3, 5, true>, range <7, 9, true>, range <11, 13, true>>> :: value << std :: endl;
    std :: cout << std :: is_same <scanners :: arithmetic <myclass> :: repeat <3, 3, mask <range <0, 2, true>, range <3, 4, false>>, 4> :: type, mask <range <3, 5, true>, range <6, 7, false>, range <7, 9, true>, range <10, 11, false>, range <11, 13, true>, range <14, 15, false>>> :: value << std :: endl;
    std :: cout << std :: is_same <scanners :: arithmetic <myclass> :: repeat <3, 4, mask <range <0, 4, false>>, 4> :: type, mask <range <3, 19, false>>> :: value << std :: endl;
}

#endif
