#ifdef __main__

#include <iostream>

#include "network/sockets/udp.h"
#include "network/dns/message.h"
#include "network/dns/query.hpp"
#include "network/dns/record.h"

void print(const network :: dns :: message & message)
{
    std :: cout  << "Id: " << message.id() << std :: endl;
    std :: cout << "Type: " << message.type() << std :: endl;
    std :: cout << "Opcode: " << message.opcode() << std :: endl;
    std :: cout << "Authoritative: " << message.authoritative() << std :: endl;
    std :: cout << "Truncated: " << message.truncated() << std :: endl;
    std :: cout << "Rescode: " << message.rescode() << std :: endl;

    std :: cout << std :: endl << "Queries (" << message.queries.size() << "):" << std :: endl << std :: endl;
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

    std :: cout << std :: endl << "Answers (" << message.answers.size() << "):" << std :: endl << std :: endl;
    for(size_t i = 0; i < message.answers.size(); i++)
    {
        message.answers[i].visit([&](const network :: dns :: record <network :: dns :: A> & record)
        {
            std :: cout << " " << i << ": " <<  record.name() << ": " << record.address() << std :: endl;
        }, [&](const network :: dns :: record <network :: dns :: null> & query)
        {
            std :: cout << " " << i << ": " << "Error" << std :: endl;
        });
    }
}

int main()
{
    network :: sockets :: udp socket;
    socket.bind(1234);

    while(true)
    {
        network :: sockets :: udp :: packet request = socket.receive();
        network :: dns :: message dnsrequest(request.message(), request.size());

        std :: cout << "Request:" << std :: endl;
        print(dnsrequest);

        std :: cout << std :: endl << std :: endl;
        socket.send({"8.8.8.8", 53}, request.message(), request.size());

        network :: sockets :: udp :: packet response = socket.receive();
        network :: dns :: message dnsresponse(response.message(), response.size());

        std :: cout << "Response:" << std :: endl;
        print(dnsresponse);
    }
}

#endif
