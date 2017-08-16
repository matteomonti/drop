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

    // Protocol

    $packet(my_packet, int);
    $packet(my_other_packet, int);
};

int main()
{
    network :: sockets :: udp my_socket;
    network :: dispatcher <my_protocol> my_dispatcher = my_socket;

    my_dispatcher.send <my_protocol :: my_other_packet> ({"127.0.0.1", 1234}, 44.4);
}

#endif
