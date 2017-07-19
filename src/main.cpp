#ifdef __main__

#include <iostream>
#include <unistd.h>
#include <thread>

#include "network/connectors/tcp.h"
#include "network/acceptors/tcp.hpp"

int main()
{
    network :: acceptors :: tcp :: async my_acceptor(1234);

    my_acceptor.on <network :: connection> ([](const network :: connection & my_connection)
    {
        my_connection.send(bytewise :: buffer("Hello World!"));
    });

    my_acceptor.on <network :: connection> ([](const network :: connection & my_connection)
    {
        my_connection.send(bytewise :: buffer("Hello Mars!"));
    });

    network :: connection my_connection = network :: connectors :: tcp :: sync :: connect({"127.0.0.1", 1234});

    std :: cout << my_connection.receive <bytewise :: buffer> () << std :: endl;
    std :: cout << my_connection.receive <bytewise :: buffer> () << std :: endl;

    my_acceptor.clear();

    my_acceptor.on <network :: connection> ([](const network :: connection & my_connection)
    {
        my_connection.send(bytewise :: buffer("Hello Venus!"));
    });

    network :: connection my_other_connection = network :: connectors :: tcp :: sync :: connect({"127.0.0.1", 1234});

    std :: cout << my_other_connection.receive <bytewise :: buffer> () << std :: endl;
}

#endif
