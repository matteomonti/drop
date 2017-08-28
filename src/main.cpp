#ifdef __main__

#include <iostream>

#include "network/sockets/udp.h"
#include "network/dns/message.h"
#include "network/dns/query.hpp"
#include "network/dns/record.h"

int main()
{
    network :: sockets :: udp socket;
    socket.bind(1234);

    while(true)
    {
        network :: sockets :: udp :: packet packet = socket.receive();
        network :: dns :: message message(packet.message(), packet.size());

        std :: cout  << "Id: " << message.id() << std :: endl;
        std :: cout << "Type: " << message.type() << std :: endl;
        std :: cout << "Opcode: " << message.opcode() << std :: endl;
        std :: cout << "Authoritative: " << message.authoritative() << std :: endl;
        std :: cout << "Truncated: " << message.truncated() << std :: endl;
        std :: cout << "Rescode: " << message.rescode() << std :: endl << std :: endl;

        std :: cout << "Queries:" << std :: endl << std :: endl;
        for(size_t i = 0; i < message.queries.size(); i++)
        {
            message.queries[i].visit([&](const network :: dns :: query <network :: dns :: A> & query)
            {
                std :: cout << " " << i << ": " <<  query.name() << std :: endl;
            }, [&](const network :: dns :: query <network :: dns :: null> & query)
            {
                std :: cout << " " << i << ": " << "Error" << std :: endl;
            });
        }
    }
}

#endif
