#ifdef __main__

#include <iostream>

#include "network/dns/dump/name.h"

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
    char message[1024];

    size_t cursor = 0;
    data :: hashtable <bytewise :: buffer, uint16_t> shortcuts;

    network :: dns :: dump :: name(message, cursor, shortcuts, "it");
    print(message, cursor);

    network :: dns :: dump :: name(message, cursor, shortcuts, "com");
    print(message, cursor);

    network :: dns :: dump :: name(message, cursor, shortcuts, "google.com");
    print(message, cursor);

    network :: dns :: dump :: name(message, cursor, shortcuts, "sub.google.com");
    print(message, cursor);

    network :: dns :: dump :: name(message, cursor, shortcuts, "my.pretty.sub.google.com");
    print(message, cursor);

    network :: dns :: dump :: name(message, cursor, shortcuts, "totally.different.domain.net");
    print(message, cursor);
}

#endif
