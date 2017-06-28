#ifdef __main__

#include <iostream>

#include "bytewise/options.h"

int main()
{
    std :: cout << "Little: " << bytewise :: endianess :: little << std :: endl;
    std :: cout << "Big: " << bytewise :: endianess :: big << std :: endl;
    std :: cout << "Network: " << bytewise :: endianess :: network << std :: endl;
    std :: cout << "Local: " << bytewise :: endianess :: local << std :: endl;

    std :: cout << bytewise :: options :: pack <bytewise :: options :: endianess :: big> :: endianess << std :: endl;
}

#endif
