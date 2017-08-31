#ifdef __main__

#include <iostream>

#include "network/dns/message.h"
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

    auto dump = message.dump();
    print(dump.message, dump.size);
}

#endif
