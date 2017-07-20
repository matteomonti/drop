#ifdef __main__

#include <iostream>
#include <unistd.h>
#include <thread>

#include "async/async.h"
#include "network/pool/pool.hpp"
#include "network/acceptors/tcp.hpp"
#include "network/connectors/tcp.h"

#define PORT 1234

struct
{
    network :: pool server;
    network :: pool client;
} pools;

promise <void> serve(const network :: pool :: connection & connection)
{
    int value;

    $
    (
        $try
        ({
            while(true)
            {
                $await(value) = connection.receive <int> ();
                $await(connection.send(value * 2));
            }
        },
        catch(...)
        {
            std :: cout << "Exception!" << std :: endl;
        });

        $return();
    )
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
    int value;
    size_t count = 0;

    $
    (
        $try
        ({
            while(true)
            {
                $await(connection.send(rand()));
                $await(value) = connection.receive <int> ();

                if(++count % 1000 == 0)
                    std :: cout << count << ": " << value << std :: endl;
            }
        },
        catch(...)
        {
            std :: cout << "Exception!" << std :: endl;
        });

        $return();
    )
}

void client()
{
    network :: connection connection = network :: connectors :: tcp :: sync :: connect({"127.0.0.1", PORT});
    request(pools.client.bind(connection));
}

int main()
{
    server();
    client();

    while(true)
        usleep(1.e6);
}

#endif
