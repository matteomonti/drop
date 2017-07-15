#ifdef __main__

#include <iostream>

#include "data/hashtable.hpp"

int main()
{
    data :: hashtable <int, int> x;

    for(size_t i = 0; i < 1048576; i++)
        x.add(i, i * 3 + 1);

    for(size_t i = 0; i < 524288; i++)
        x.remove(rand() % 1048576);

    for(size_t i = 0; i < 1048576; i++)
    {
        data :: optional <int> value = x[i];
        if(value)
            std :: cout << *value << std :: endl;
        else
            std :: cout << "(empty)" << std :: endl;
    }
}

#endif
