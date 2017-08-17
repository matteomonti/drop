#ifdef __main__

#include <iostream>
#include <unistd.h>
#include <thread>

#include "network/packet/packet.hpp"

class my_protocol
{
    // Self

    typedef my_protocol self;

public:

    // Protocol

    $packet(my_packet, int);
    $packet(my_other_packet, int, double);
};

int main()
{
    my_protocol :: my_packet my_packet(network :: address{"127.0.0.1", 1234}, 44);
    my_protocol :: my_other_packet my_other_packet(network :: address{"127.0.0.1", 1234}, bytewise :: tuple <int, double> {44, 55.6});
}

#endif
