#ifdef __main__

#include <iostream>
#include <unistd.h>
#include <thread>

#include "network/packet/macros.h"
#include "network/packet/count.h"
#include "network/packet/in.h"

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

    class fake_third_packet
    {
    };
};

int main()
{
    std :: cout << network :: packet :: in <myclass, myclass :: first_packet> :: value << std :: endl;
    std :: cout << network :: packet :: in <myclass, myclass :: second_packet> :: value << std :: endl;
    std :: cout << network :: packet :: in <myclass, myclass :: fake_third_packet> :: value << std :: endl;
}

#endif
