#ifdef __main__

#include <iostream>
#include <type_traits>
#include <string>
#include <iomanip>

#include "bytewise/block.hpp"

void f(char (&bytes)[12])
{
    std :: cout << "Ok" << std :: endl;
}

int main()
{
    bytewise :: block <12> my_block;
    f(my_block);
}

#endif
