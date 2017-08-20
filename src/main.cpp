#ifdef __main__

#include <iostream>
#include <unistd.h>
#include <thread>

#include "network/pool/pool.hpp"
#include "network/acceptors/tcp.hpp"
#include "network/connectors/tcp.h"
#include "network/pool/pool.hpp"
#include "async/async.h"
#include "chrono/crontab.h"

chrono :: crontab crontab;
network :: pool pool;

promise <void> server(const network :: pool :: connection & connection)
{
    int request;

    $async
    (
        while(true)
        {
            $await(request) = connection.receive <int> ();
            $await(connection.send(request * 2));
        }
    );
}

promise <void> client(const network :: pool :: connection & connection)
{
    int response;

    $async
    (
        while(true)
        {
            $await(connection.send(rand()));
            $await(response) = connection.receive <int> ();

            std :: cout << response << std :: endl;
            $await(crontab.wait(1e6));
        }
    );
}

int main()
{
    network :: acceptors :: tcp :: async my_acceptor(1234);
    my_acceptor.on <network :: connection> ([](const network :: connection & connection)
    {
        server(pool.bind(connection));
    });

    network :: connectors :: tcp :: async my_connector;
    my_connector.connect({"127.0.0.1", 1234}).then([](const network :: connection & connection)
    {
        client(pool.bind(connection));
    });

    while(true)
        usleep(1.e6);
}

#endif
