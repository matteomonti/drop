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
    bytewise :: buffer value = my_connection.receive <bytewise :: buffer> ();

    std :: cout << "Value: " << value << std :: endl;
}

void client()
{
    network :: connection my_connection = network :: connectors :: tcp :: sync :: connect({"localhost", 1234});
    my_connection.send <bytewise :: buffer> ("Hello, world?");
}

int main()
{
    std :: thread server_thread(server);
    client();
    server_thread.join();
}

#endif
