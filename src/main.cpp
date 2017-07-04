#ifdef __main__

#include <iostream>
#include <type_traits>
#include <string>
#include <iomanip>

#include "bytewise/macros.h"
#include "bytewise/serialize.hpp"
#include "bytewise/deserialize.hpp"

int main()
{
    int x = 3;
    auto y = bytewise :: serialize(x);
    int z = bytewise :: deserialize <int> (y);

    std :: cout << z << std :: endl;
}

#endif
