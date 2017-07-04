#ifdef __main__

#include <iostream>
#include <type_traits>
#include <string>
#include <iomanip>
#include <thread>

#include "network/connectors/tcp.h"
#include "network/acceptors/tcp.h"

network :: connection * the_connection;

void receive()
{
    network :: connection & connection = *the_connection;
    while(true)
        std :: cout << connection.receive <bytewise :: buffer> () << std :: endl;
}

void send(network :: connection & connection)
{
    while(true)
    {
        char buffer[1024];
        std :: cin.getline(buffer, 1024);

        connection.send(bytewise :: buffer {buffer});
    }
}

void server()
{
    network :: acceptors :: tcp :: sync my_acceptor(1230);
    network :: connection my_connection = my_acceptor.accept();

    std :: cout << "Connection received" << std :: endl;
    the_connection = &my_connection;
    std :: thread recvthread(receive);
    send(my_connection);
}

void client()
{
    network :: connection my_connection = network :: connectors :: tcp :: sync :: connect({"localhost", 1230});
    std :: cout << "Connected" << std :: endl;
    the_connection = &my_connection;
    std :: thread recvthread(receive);
    send(my_connection);
}

int main(int narg, char ** args)
{
    if(narg != 2)
        return -1;

    if(!strcmp(args[1], "client"))
        client();
    else if(!strcmp(args[1], "server"))
        server();
}

#endif
