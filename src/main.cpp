#ifdef __main__

#include <iostream>
#include <type_traits>

#include "bytewise/mask.h"

int main()
{
    using namespace bytewise;

    typedef mask
    <
        range <7, 8, true>,
        range <3, 4, false>,
        range <14, 16, false>,
        range <16, 17, true>,
        range <11, 12, false>,
        range <2, 3, false>,
        range <4, 5, true>,
        range <8, 9, false>,
        range <12, 14, false>
    > :: compress :: type type;

    std :: cout << std :: is_same
    <
        type,
        mask <range <2, 4, false>, range <4, 5, true>, range <7, 8, true>, range <8, 9, false>, range <11, 16, false>, range <16, 17, true>>
    > :: value << std :: endl;

    std :: cout << type :: size << std :: endl;
}

#endif
