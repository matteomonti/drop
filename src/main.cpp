#ifdef __main__

#include <iostream>
#include <unistd.h>
#include <thread>

#include "bytewise/bytewise.h"

class myclass
{
public:

    // Self

    typedef myclass self;

    // Members

    int i;
    int j;
    bytewise :: buffer k;

    // Bytewise

    $bytewise(i);
    $bytewise(j);
    $bytewise(k);
};

int main()
{
    auto x = bytewise :: serialize(13, 14, bytewise :: buffer("Hello World!"));
    auto y = bytewise :: deserialize <int, int, bytewise :: buffer> (x);

    std :: cout << y.get <0> () << std :: endl;
    std :: cout << y.get <1> () << std :: endl;
    std :: cout << y.get <2> () << std :: endl;
}

#endif
