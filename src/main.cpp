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

public:

    // Packets

    $packet(first_packet, int);
    $packet(second_packet, double, char);
};

int main()
{
    std :: cout << myclass :: first_packet :: index << std :: endl;
    std :: cout << myclass :: second_packet :: index << std :: endl;
}

#endif
