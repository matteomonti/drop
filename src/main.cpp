#ifdef __main__

#include <iostream>

#include "bytewise/macros.h"
#include "bytewise/count.h"

class myclass
{
    // Self

    typedef myclass self;

    // Members

    int n;
    double k;
    char l;

    // Bytewise

    bytewise(n);
    bytewise(k);
    bytewise(l);
};

int main()
{
    std :: cout << bytewise :: count <myclass> :: value << std :: endl;
}

#endif
