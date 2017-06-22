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

    bytewise :: buffer w1;
    bytewise :: buffer w2;

    int x;
    double y;
    char z[4];

    // Bytewise

    bytewise(w1);
    bytewise(w2);

    bytewise(x);
    bytewise(y);
    bytewise(z);
};

int main()
{
    myclass myobj;
    myobj.w1 = "Hello, world!";
    myobj.w2 = "Repeating myself, repeating myself, repeating myself, repeating myself, repeating myself, repeating myself, repeating myself, repeating myself, repeating myself, repeating myself, repeating myself, repeating myself, repeating myself, repeating myself, repeating myself, repeating myself, repeating myself, repeating myself, repeating myself.";

    myobj.x = 3;
    myobj.y = 4.5;

    myobj.z[0] = 6;
    myobj.z[1] = 7;
    myobj.z[2] = 8;
    myobj.z[3] = 9;

    auto bytes = bytewise :: serialize(myobj);

    for(size_t i = 0; i < bytes.size(); i++)
    {
        std :: cout << std :: setw(5) << (unsigned int) (unsigned char) bytes[i];

        if(i % 16 == 15)
            std :: cout << std :: endl;
    }

    std :: cout << std :: endl;

    myclass myotherobj = bytewise :: deserialize <myclass> (bytes);

    std :: cout << myotherobj.w1 << std :: endl;
    std :: cout << myotherobj.w2 << std :: endl;

    std :: cout << myotherobj.x << std :: endl;
    std :: cout << myotherobj.y << std :: endl;

    std :: cout << (unsigned int) (unsigned char) myotherobj.z[0] << std :: endl;
    std :: cout << (unsigned int) (unsigned char) myotherobj.z[1] << std :: endl;
    std :: cout << (unsigned int) (unsigned char) myotherobj.z[2] << std :: endl;
    std :: cout << (unsigned int) (unsigned char) myotherobj.z[3] << std :: endl;
}

#endif
