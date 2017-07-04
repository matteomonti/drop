#ifdef __main__

#include <iostream>
#include <type_traits>
#include <string>
#include <iomanip>
#include <thread>

#include "network/connectors/tcp.h"
#include "network/acceptors/tcp.h"

void server()
{
    network :: acceptors :: tcp :: sync my_acceptor(1232);
    network :: connection my_connection = my_acceptor.accept();
    int value = my_connection.receive <int> ();

    std :: cout << "Received: " << value << std :: endl;
}

void client()
{
    network :: connection my_connection = network :: connectors :: tcp :: sync :: connect({"localhost", 1232});
    my_connection.send(44);
}

int main()
{
    std :: thread server_thread(server);
    usleep(1.e5);
    std :: thread client_thread(client);

    server_thread.join();
    client_thread.join();
}

#endif
