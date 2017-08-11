#ifdef __main__

#include <iostream>
#include <unistd.h>
#include <thread>

#include "network/packet/macros.h"
#include "network/packet/count.h"

class myotherclass
{
};

class myclass
{
    // Self

    typedef myclass self;

    // Packets

    $packet(first_packet, int);
    $packet(second_packet, double, int, char, myotherclass);
};

int main()
{
    std :: cout << network :: packet :: count <myclass> :: value << std :: endl;
}

#endif
