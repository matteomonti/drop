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
    $packet(my_other_packet, int, double);
};

int main()
{
    network :: sockets :: udp my_socket;
    my_socket.bind(1235);
    network :: dispatcher <my_protocol> my_dispatcher(my_socket);

    my_dispatcher.receive <my_protocol :: my_packet> ();
}

#endif
