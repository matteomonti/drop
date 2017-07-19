#ifdef __main__

#include <iostream>
#include <unistd.h>
#include <thread>

#include "network/pool/pool.hpp"
#include "network/acceptors/tcp.hpp"
#include "network/connectors/tcp.h"

#define PORT 1234

struct
{
    network :: pool server;
    // network :: pool client;
} pools;

promise <void> serve(const network :: pool :: connection & connection)
{
    return connection.receive <int> ().then([=](const int & value)
    {
        return connection.send(value * 2);
    }).then([=]()
    {
        return serve(connection);
    }).except([](const std :: exception_ptr &)
    {
    });
}

void server()
{
    static network :: acceptors :: tcp :: async acceptor(PORT);
    acceptor.on <network :: connection> ([](const network :: connection & connection)
    {
        serve(pools.server.bind(connection));
    });
}

size_t count = 0;

promise <void> request(const network :: pool :: connection & connection)
{
    return connection.send(rand()).then([=]()
    {
        return connection.receive <int> ();
    }).then([=](const int & value)
    {
        if(++count % 1000 == 0)
            std :: cout << count << ": " << value << std :: endl;

        return request(connection);
    }).except([](const std :: exception_ptr &)
    {
    });
}

void client()
{
    network :: connection connection = network :: connectors :: tcp :: sync :: connect({"127.0.0.1", PORT});
    // request(pools.client.bind(connection));
}

int main()
{
    server();
    // client();

    while(true)
        usleep(1.e6);
}

#endif
