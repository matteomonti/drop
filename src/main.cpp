#ifdef __main__

#include <iostream>
#include <type_traits>

#include "bytewise/map.h"

int main()
{
    using namespace bytewise;
    std :: cout << std :: is_same <map <path <0, 1, 2>, path <3, 4, 5>> :: append <map <path <6, 7, 8>>> :: type :: prefix <14> :: type, map <path <14, 0, 1, 2>, path <14, 3, 4, 5>, path <14, 6, 7, 8>>> :: value << std :: endl;
}

#endif
