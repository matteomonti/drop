#ifdef __main__

#include <iostream>
#include <unistd.h>
#include <thread>

#include "network/connectors/tcp.h"

int main()
{
    network :: connectors :: tcp :: async my_connector;

    my_connector.connect({"google.it", 79}).then([](const network :: connection & connection)
    {
        std :: cout << "Connection successful" << std :: endl;
    }).except([](const std :: exception_ptr & exception)
    {
        try
        {
            std :: rethrow_exception(exception);
        }
        catch(const std :: exception & exception)
        {
            std :: cout << exception.what() << std :: endl;
        }
    });

    usleep(rand() % 100000);

    while(true)
        usleep(1.e6);
}

#endif
