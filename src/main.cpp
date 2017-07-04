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
    network :: acceptors :: tcp :: sync my_acceptor(1230);
    network :: connection my_connection = my_acceptor.accept();
    auto value = my_connection.receive <bytewise :: buffer> ();

    std :: cout << "Received: " << value << std :: endl;
}

void client()
{
    network :: connection my_connection = network :: connectors :: tcp :: sync :: connect({"localhost", 1230});
    my_connection.send(bytewise :: buffer{"Hello World!"});
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
