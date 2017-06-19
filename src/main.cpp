#ifdef __main__

#include <iostream>
#include <type_traits>

#include "bytewise/mask.h"

int main()
{
    using namespace bytewise;

    std :: cout << std :: is_same <mask <range <0, 1, false>, range <2, 3, true>> :: append <mask <range <4, 5, false>, range <6, 7, true>>> :: type :: shift <3> :: type, mask <range <3, 4, false>, range <5, 6, true>, range <7, 8, false>, range <9, 10, true>>> :: value << std :: endl;
}

#endif
