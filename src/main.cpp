#ifdef __main__

#include <iostream>
#include <unistd.h>
#include <thread>

#include "network/acceptors/tcp.hpp"

int main()
{
    network :: acceptors :: tcp :: async my_acceptor(1234);
    my_acceptor.on <network :: connection> ([](const network :: connection & my_connection)
    {
        my_connection.send(bytewise :: buffer("Hello World!"));
    });

    while(true)
        usleep(1.e6);
}

#endif
