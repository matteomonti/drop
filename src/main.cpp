#ifdef __main__

#include <iostream>
#include <unistd.h>
#include <thread>

#include "network/connectors/tcp.h"

int main()
{
    network :: connectors :: tcp :: async my_connector;

    usleep(1.e5);

    my_connector.connect({"google.it", 80}).then([](const network :: connection & connection)
    {
        std :: cout << "Connected." << std :: endl;
    }).except([](std :: exception_ptr exception)
    {
        try
        {
            std :: rethrow_exception(exception);
        }
        catch(const std :: exception & exception)
        {
            std :: cout << "Exception: " << exception.what() << std :: endl;
        }
    });

    while(true)
        usleep(1.e6);
}

#endif
