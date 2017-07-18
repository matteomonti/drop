#ifdef __main__

#include <iostream>
#include <unistd.h>
#include <thread>

#include "network/acceptors/tcp.h"
#include "network/connectors/tcp.h"
#include "network/pool/pool.hpp"

void server()
{
    network :: pool my_pool;

    network :: acceptors :: tcp :: sync my_acceptor(1234);
    network :: connection my_connection = my_acceptor.accept();

    network :: pool :: connection my_pool_connection = my_pool.bind(my_connection);
    my_pool_connection.receive <int> ().then([=](const int & value)
    {
        std :: cout << "Received " << value << std :: endl;
        return my_pool_connection.receive <bytewise :: buffer> ();
    }).then([=](const bytewise :: buffer & value)
    {
        std :: cout << "Received " << value << std :: endl;
        return my_pool_connection.send(99);
    }).then([=]()
    {
        std :: cout << "Sent number" << std :: endl;
        return my_pool_connection.send(bytewise :: buffer("Hello to you my friend!"));
    }).then([=]()
    {
        std :: cout << "Sent message" << std :: endl;
    });

    while(true)
        usleep(1.e6);
}

void client()
{
    network :: connection my_connection = network :: connectors :: tcp :: sync :: connect({"localhost", 1234});
    my_connection.send(55);
    my_connection.send(bytewise :: buffer("Hello there!"));

    {
        int value = my_connection.receive <int> ();
        std :: cout << "Blockingly received " << value << std :: endl;
    }

    {
        bytewise :: buffer value = my_connection.receive <bytewise :: buffer> ();
        std :: cout << "Blockingly received " << value << std :: endl;
    }

    while(true)
        usleep(1.e6);
}

int main()
{
    std :: thread server_thread(server);
    client();

    server_thread.join();
}

#endif
