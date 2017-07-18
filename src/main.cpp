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
}

void client()
{
    network :: connection my_connection = network :: connectors :: tcp :: sync :: connect({"localhost", 1234});
}

int main()
{
    std :: thread server_thread(server);
    client();
    server_thread.join();
}

#endif
