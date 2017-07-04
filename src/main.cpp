#ifdef __main__

#include <iostream>
#include <type_traits>
#include <string>
#include <iomanip>

#include "data/variant.hpp"

class myclass
{
public:

    void f() const // REMOVE ME
    {
        std :: cout << "Hello from my class" << std :: endl;
    }
};

class myotherclass
{
public:

    void f() const // REMOVE ME
    {
        std :: cout << "Hello from my other class" << std :: endl;
    }
};

int main()
{
    auto my_variant = data :: variant <int, double, myclass, myotherclass> :: construct <myclass> ();

    my_variant.visit([](double & value)
    {
        std :: cout << "Double value is: " << value << std :: endl;
    },
    [](int & value)
    {
        std :: cout << "Int value is: " << value << std :: endl;
        value++;
    },
    [](auto & value)
    {
        std :: cout << "Is myclass&: " << std :: is_same <decltype(value), myclass &> :: value << std :: endl;
        std :: cout << "Either myclass or myotherclass" << std :: endl;
        value.f();
    });
}

#endif
