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

    size_t total = 0;
    for(size_t n = 0;; n++)
    {
        if(n % 1000000 == 0)
            std :: cout << n << "  (" << total << ")"<< std :: endl;

        message[0] = rand();
        message[1] = rand();

        network :: dns :: message dnsmessage(message, size);
        total += dnsmessage.queries.size();
    }
}

#endif
