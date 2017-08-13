#ifdef __main__

#include <iostream>
#include <unistd.h>
#include <thread>

#include "bytewise/tuple.hpp"

int main()
{
    bytewise :: tuple <int, char, float, double> my_tuple(3, 'q', 4.44, 5.13);

    std :: cout << my_tuple.get <0> () << std :: endl;
    std :: cout << my_tuple.get <1> () << std :: endl;
    std :: cout << my_tuple.get <2> () << std :: endl;
    std :: cout << my_tuple.get <3> () << std :: endl << std :: endl;

    my_tuple.visit([](int & a, char & b, float & c, double & d)
    {
        a = 4;
        b = 'x';
        c = 5.55;
        d = 6.26;
    });

    std :: cout << my_tuple.get <0> () << std :: endl;
    std :: cout << my_tuple.get <1> () << std :: endl;
    std :: cout << my_tuple.get <2> () << std :: endl;
    std :: cout << my_tuple.get <3> () << std :: endl << std :: endl;
}

#endif
