#ifdef __main__

#include <iostream>
#include <unistd.h>
#include <thread>

#include "network/dispatcher.hpp"

class myotherclass
{
};

class myprotocol
{
    // Self

    typedef myprotocol self;

public:

    // Packets

    $packet(first_packet, int);
    $packet(second_packet, double, char);
};

int main()
{
    network :: sockets :: udp my_socket;
    my_socket.bind(1234);

    network :: dispatcher <myprotocol> my_dispatcher(my_socket);
    my_dispatcher.send <myprotocol :: first_packet> (44);
    my_dispatcher.send <myprotocol :: second_packet> (4.44, '4');
}

#endif
