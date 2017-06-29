#ifdef __main__

#include <iostream>
#include <type_traits>
#include <string>
#include <iomanip>

#include "data/variant.hpp"

int main()
{
    std :: cout << data :: variant <int, double, char, float, int *, double *, char *> :: id <char *> :: value << std :: endl;
}

#endif
