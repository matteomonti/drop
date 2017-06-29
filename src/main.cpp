#ifdef __main__

#include <iostream>
#include <type_traits>
#include <string>
#include <iomanip>

#include "data/variant.hpp"

int main()
{
    data :: variant <int, double> my_variant = data :: variant <int, double> :: construct <int> ();

    my_variant.visit([](auto && value)
    {
        value = 12;
    });

    my_variant.visit([](auto && value)
    {
        std :: cout << value << std :: endl;
    });
}

#endif
