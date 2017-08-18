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
    $packet(my_other_packet, int, bytewise :: buffer);
};

int main()
{
    network :: sockets :: udp my_socket;
    my_socket.bind(1234);

    network :: dispatcher <my_protocol> my_dispatcher(my_socket);
    data :: variant <my_protocol :: my_packet, my_protocol :: my_other_packet> my_packet = my_dispatcher.receive <my_protocol :: my_packet, my_protocol :: my_other_packet> ();

    my_packet.visit([](const my_protocol :: my_packet & packet)
    {
        std :: cout << "Received my_packet from " << packet.remote() << " with value " << packet.message() << std :: endl;
    }, [](const my_protocol :: my_other_packet & packet)
    {
        std :: cout << "Received my_other_packet from " << packet.remote() << " with value " << packet.message <0> () << " and message " << packet.message <1> () << std :: endl;
    });
}

#endif
