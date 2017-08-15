#ifdef __main__

#include <iostream>
#include <unistd.h>
#include <thread>

#include "network/dispatcher.hpp"

class my_protocol
{
    // Self

    typedef my_protocol self;

public:

    // Packets

    $packet(first_packet, int);
    $packet(second_packet, double);
    $packet(third_packet, int, double, char);
};

int main()
{
    network :: sockets :: udp my_socket;
    network :: dispatcher <my_protocol> my_dispatcher = my_socket;
    my_dispatcher.send <my_protocol :: first_packet> ({"127.0.0.1", 1235}, 55.2);
}

#endif
