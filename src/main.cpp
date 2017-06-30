#ifdef __main__

#include <iostream>
#include <type_traits>
#include <string>
#include <iomanip>

#include "data/variant.hpp"

class unmovable
{
public:

    unmovable() = default;
    unmovable(const unmovable &) = default;
    unmovable(unmovable &&) = delete;

    int x;

    void operator = (int x)
    {
        this->x = x;
    };

    operator int()
    {
        return x;
    }
};

typedef data :: variant <int, double, unmovable> my_variant_type;

my_variant_type f()
{
    my_variant_type my_variant = my_variant_type :: construct <int> ();

    my_variant.visit([](auto && value)
    {
        value = 12;
    });

    return my_variant;
}

int main()
{
    my_variant_type my_variant = f();
    my_variant.visit([](auto && value)
    {
        std :: cout << value << std :: endl;
    });

    my_variant_type my_other_variant = std :: move(my_variant);
    my_other_variant.visit([](auto && value)
    {
        std :: cout << value << std :: endl;
    });

    my_variant_type yet_another_variant = my_other_variant;
    yet_another_variant.visit([](auto && value)
    {
        std :: cout << value << std :: endl;
    });
}

#endif
