#ifdef __main__

#include <iostream>
#include <unistd.h>
#include <thread>

#include "bytewise/bytewise.h"

int main()
{
    auto bytes = bytewise :: serialize <bytewise :: options :: pad :: beg <15>, bytewise :: options :: pad :: end <3>> (44, 12);

    for(size_t i = 0; i < bytes.size(); i++)
        std :: cout << (unsigned int) bytes[i] << std :: endl;
}

#endif
