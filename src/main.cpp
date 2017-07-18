#ifdef __main__

#include <iostream>
#include <unistd.h>
#include <thread>

#include "network/acceptors/tcp.h"
#include "network/connectors/tcp.h"

void server()
{
    network :: acceptors :: tcp :: sync my_acceptor(1234);
    network :: connection my_connection = my_acceptor.accept();
    std :: cout << my_connection.receive <int> () << std :: endl;
    std :: cout << my_connection.receive <int> () << std :: endl;
}

void client()
{
    network :: connection my_connection = network :: connectors :: tcp :: sync :: connect({"localhost", 1234});
    my_connection.send(44);
}

int main()
{
    std :: thread server_thread(server);
    client();
    server_thread.join();
}

#endif
