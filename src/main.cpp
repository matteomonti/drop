#ifdef __main__

#include <iostream>

#include "network/sockets/udp.h"
#include "network/dns/message.h"
#include "network/dns/query.hpp"

int char2int(char input)
{
    if(input >= '0' && input <= '9')
        return input - '0';
    if(input >= 'A' && input <= 'F')
        return input - 'A' + 10;
    if(input >= 'a' && input <= 'f')
        return input - 'a' + 10;
}

size_t hex2bin(char* target, const char* src)
{
    size_t size = 0;

    while(*src && src[1])
    {
        if(*src == ' ')
        {
            src++;
            continue;
        }

        *(target++) = char2int(*src)*16 + char2int(src[1]);
        src += 2;
        size++;
    }

    return size;
}

int main()
{
    const char hex[] =
   "50 7d 01 00 00 06 00 00 00 00 00 00 \
    06 67 6f 6f 67 6c 65 02 69 74 00 00 01 00 01\
    03 73 75 62 c0 0c 00 01 00 01\
    03 73 75 62 c0 1b 00 01 00 01\
    c0 25 00 01 00 01\
    c0 2f 00 01 00 01\
    03 61 73 64 03 61 73 64 03 61 73 64 03 61 73 64 03 61 73 64 03 61 73 64 03 61 73 64 03 61 73 64 03 61 73 64 03 61 73 64 03 61 73 64 03 61 73 64 03 61 73 64 03 61 73 64 03 61 73 64 03 61 73 64 03 61 73 64 00 00 01 00 01";

    char message[512];

    size_t size = hex2bin(message, hex);
    network :: dns :: message dnsmessage(message, size);

    std :: cout  << "Id: " << dnsmessage.id() << std :: endl;
    std :: cout << "Type: " << dnsmessage.type() << std :: endl;
    std :: cout << "Opcode: " << dnsmessage.opcode() << std :: endl;
    std :: cout << "Authoritative: " << dnsmessage.authoritative() << std :: endl;
    std :: cout << "Truncated: " << dnsmessage.truncated() << std :: endl;
    std :: cout << "Rescode: " << dnsmessage.rescode() << std :: endl << std :: endl;

    std :: cout << "Queries:" << std :: endl << std :: endl;
    for(size_t i = 0; i < dnsmessage.queries.size(); i++)
    {
        dnsmessage.queries[i].visit([&](const network :: dns :: query <network :: dns :: A> & query)
        {
            std :: cout << " " << i << ": " <<  query.name() << std :: endl;
        }, [&](const network :: dns :: query <network :: dns :: null> & query)
        {
            std :: cout << " " << i << ": " << "Error" << std :: endl;
        });
    }
}

#endif
