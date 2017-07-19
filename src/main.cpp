#ifdef __main__

#include <iostream>
#include <unistd.h>
#include <thread>

#include "network/connectors/tcp.h"
#include "network/acceptors/tcp.hpp"
#include "network/pool/pool.hpp"
#include "async/async.h"

struct
{
    network :: pool server;
    network :: pool client;
} pools;

promise <void> serve(const network :: pool :: connection & connection)
{
    return connection.receive <int> ().then([=](const int & value)
    {
        return connection.send(value * 2);
    });
}

void server()
{
    network :: acceptors :: tcp :: async * acceptors[16];
    for(size_t i = 0; i < 16; i++)
        acceptors[i] = new (class network :: acceptors :: tcp :: async){2000 + i};

    for(size_t i = 0; i < 16; i++)
        acceptors[i]->on <network :: connection> ([](const network :: connection & connection)
        {
            serve(pools.server.bind(connection));
        });
}

volatile int count = 0, total = 0;

promise <void> request(const network :: pool :: connection & connection)
{
    return connection.send(rand()).then([=]()
    {
        return connection.receive <int> ();
    }).then([](const int & value)
    {
        total += value;
        std :: cout << count++ << ": " << total << std :: endl;

        promise <void> done;
        done.resolve();
        return done;
    });
}

void client()
{
    std :: cout << "Connecting" << std :: endl;
    network :: connection connection = network :: connectors :: tcp :: sync :: connect({"127.0.0.1", 2000 + ((unsigned int) rand() % 16)});
    std :: cout << "Pushing" << std :: endl;
    request(pools.client.bind(connection));
    std :: cout << "Pushed" << std :: endl;
}

int main()
{
    srand(time(nullptr));

    server();

    for(size_t i = 0;; i++)
    {
        client();
        usleep(1.e3);
    }

    while(true)
        usleep(1.e6);
}

#endif
