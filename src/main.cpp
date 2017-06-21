#ifdef __main__

#include <iostream>
#include <type_traits>

#include "bytewise/endianess.hpp"

int main()
{
    char x[17] = "yodamamapapadada";
    char y[17];
    y[16] = '\0';

    bytewise :: endianess :: translate((char (&)[16]) y, (const char (&)[16])x);
    std :: cout << y << std :: endl;
}

#endif
