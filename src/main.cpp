#ifdef __main__

#include <iostream>
#include <unistd.h>
#include <thread>

#include "bytewise/bytewise.h"

int main()
{
    auto bytes = bytewise :: serialize(4.44, 2, 'a', bytewise :: buffer("Hello World!"), 9.1);
    auto values = bytewise :: deserialize <double, int, char, bytewise :: buffer, double> (bytes);

    values.visit([](double & a, int & b, char & c, bytewise :: buffer & d, double & e)
    {
        std :: cout << a << std :: endl;
        std :: cout << b << std :: endl;
        std :: cout << c << std :: endl;
        std :: cout << d << std :: endl;
        std :: cout << e << std :: endl;
    });
}

#endif
