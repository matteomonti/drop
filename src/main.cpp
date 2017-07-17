#ifdef __main__

#include <iostream>
#include <unistd.h>
#include <thread>

#include "data/heap.hpp"

int main()
{
    data :: heap <size_t> my_heap;

    for(size_t i = 0; i < 1048576; i++)
        my_heap.push(rand());

    for(size_t i = 0; i < 1048576; i++)
        std :: cout << my_heap.pop() << std :: endl;
}

#endif
