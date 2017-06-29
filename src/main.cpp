#ifdef __main__

#include <iostream>
#include <type_traits>
#include <string>
#include <iomanip>

#include "data/variant.hpp"

data :: variant_base <int, double> f()
{
    data :: variant_base <int, double> my_variant = data :: variant_base <int, double> :: construct <int> ();

    my_variant.visit([](auto && value)
    {
        value = 12;
    });

    return my_variant;
}

int main()
{
    data :: variant_base <int, double> my_variant = f();
    my_variant.visit([](auto && value)
    {
        std :: cout << value << std :: endl;
    });

    data :: variant_base <int, double> my_other_variant = std :: move(my_variant);
    my_other_variant.visit([](auto && value)
    {
        std :: cout << value << std :: endl;
    });

    data :: variant_base <int, double> yet_another_variant = my_other_variant;
    yet_another_variant.visit([](auto && value)
    {
        std :: cout << value << std :: endl;
    });
}

#endif
