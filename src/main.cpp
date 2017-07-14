#ifdef __main__

#include <iostream>

#include "network/pool/queue.hpp"
#include "network/sockets/tcp.h"

int main()
{
    network :: queue my_queue;
    network :: sockets :: tcp my_socket;

    std :: cout << "My socket descriptor: " << my_socket.descriptor() << std :: endl;

    my_socket.block(false);
    my_queue.add <network :: queue :: write> (my_socket.descriptor());
    my_socket.connect({"google.com", 80});

    size_t events = my_queue.select();
    std :: cout << "Events (" << events << "):" << std :: endl;

    for(size_t i = 0; i < events; i++)
        std :: cout << my_queue[i] << std :: endl;
}

#endif
