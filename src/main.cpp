#ifdef __main__

#include <iostream>

#include "network/dns/message.hpp"
#include "network/sockets/udp.h"

void print(char * message, const size_t & cursor)
{
    for(size_t i = 0; i < cursor; i++)
    {
        if(message[i] >= 'a' && message[i] <= 'z')
            printf("%c", message[i]);
        else
            printf("[%02x]", (unsigned int) (unsigned char) message[i]);
    }

    std :: cout << std :: endl << std :: endl;
}

int main()
{
    network :: sockets :: udp socket;
    socket.bind(1234);

    auto packet = socket.receive();
    network :: dns :: message message(packet.message(), packet.size());

    message.queries[0].visit([&](const network :: dns :: query <network :: dns :: A> & query)
    {
        message.answer(network :: dns :: record <network :: dns :: A> (query.name(), network :: dns :: internet, 60, network :: address("127.0.0.1", 0).ip()), true);
        auto dump = message.dump();

        std :: cout << "Should send to " << packet.remote() << std :: endl << std :: endl;
        print(dump.message, dump.size);
        socket.send(packet.remote(), dump.message, dump.size);
    });
}

#endif
