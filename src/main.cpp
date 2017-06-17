#ifdef __main__

#include <iostream>

#include "progressive/macros.h"
#include "progressive/counter.h"

class myclass
{
public:

    template <size_t, bool> struct myscope;

    template <bool dummy> struct myscope <0, dummy>
    {
        static constexpr bool exists = true;
    };

    template <bool dummy> struct myscope <1, dummy>
    {
        static constexpr bool exists = true;
    };
};

int main()
{
    std :: cout << progressive :: counter <myclass :: myscope, 0> :: value << std :: endl;
}

#endif
