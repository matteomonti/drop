#ifdef __main__

#include <iostream>
#include <type_traits>
#include <string>
#include <iomanip>

#include "bytewise/on.hpp"
#include "bytewise/macros.h"

class a
{
    // Self

    typedef a self;

    // Members

    int x;

    // Bytewise

    bytewise(x);

    // Methods

    void on(bytewise :: read)
    {
        std :: cout << "Event read emitted!" << std :: endl;
    }
};

int main()
{
    a mya;
    bytewise :: on <a, bytewise :: read> :: emit(mya);
}

#endif
