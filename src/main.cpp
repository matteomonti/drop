#ifdef __main__

#include <iostream>
#include <unistd.h>
#include <thread>

#include "network/acceptors/tcp.h"
#include "network/connectors/tcp.h"

struct myclass
{
    // Self

    typedef myclass self;

    // Members

    bytewise :: buffer buffer;

    // Bytewise

    bytewise(buffer);
};

void server()
{
    network :: acceptors :: tcp :: sync my_acceptor(1234);
    network :: connection my_connection = my_acceptor.accept();
    myclass value = my_connection.receive <myclass> ();

    std :: cout << "Value: " << value.buffer << std :: endl;
}

void client()
{
    network :: connection my_connection = network :: connectors :: tcp :: sync :: connect({"localhost", 1234});
    my_connection.send <myclass> ({.buffer = "Hello World!!"});
}

int main()
{
    std :: thread server_thread(server);
    client();
    server_thread.join();
}

#endif
