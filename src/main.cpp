#ifdef __main__

#include <iostream>

#include "pmurhash32/pmurhash32.h"

int main()
{
    char string[128];
    memset(string, 'x', 128);

    uint32_t total = 0;
    for(reinterpret_cast <size_t &> (string[0]) = 0;; reinterpret_cast <size_t &> (string[0])++)
    {
        if(reinterpret_cast <size_t &> (string[0]) % 1000000 == 0)
            std :: cout << reinterpret_cast <size_t &> (string[0]) << " (" << total << ")" << std :: endl;

        total += PMurHash32(0, string, 128);
    }
}

#endif
