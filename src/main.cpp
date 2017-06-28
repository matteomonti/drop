#ifdef __main__

#include <iostream>
#include <type_traits>
#include <string>
#include <iomanip>

#include "bytewise/macros.h"
#include "bytewise/serialize.hpp"
#include "bytewise/deserialize.hpp"

class myclass
{
public:

    // Self

    typedef myclass self;

    // Members

    int x;

    // Bytewise

    bytewise(x, endianess :: local);
};

int main()
{
    myclass myobj;
    myobj.x = 4;

    auto bytes = bytewise :: serialize(myobj);

    for(size_t i = 0; i < bytes.size(); i++)
    {
        std :: cout << std :: setw(5) << (unsigned int) (unsigned char) bytes[i];

        if(i % 16 == 15)
            std :: cout << std :: endl;
    }

    std :: cout << std :: endl;

    myclass myotherobj = bytewise :: deserialize <myclass> (bytes);

    std :: cout << myotherobj.x << std :: endl;
}

#endif
