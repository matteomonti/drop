#ifdef __main__

#include <iostream>

#include "progressive/macros.h"
#include "progressive/exists.h"

class myclass
{
public:

    template <size_t, bool> struct myscope;

    template <bool dummy> struct myscope <0, dummy>
    {
        static constexpr bool exists = true;
    };
};

int main()
{
    std :: cout << progressive :: exists <myclass :: myscope, 0, 0> :: value << std :: endl;
    std :: cout << progressive :: exists <myclass :: myscope, 1, 0> :: value << std :: endl;
}

#endif
