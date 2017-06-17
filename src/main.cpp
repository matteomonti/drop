#ifdef __main__

#include <iostream>

#include "bytewise/buffer.h"

int main()
{
    bytewise :: buffer my_buffer("Hello World!");
    std :: cout << my_buffer << std :: endl;
}

#endif
