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

    for(size_t i = 0;; i++)
    {
        if(i % 1000000 == 0)
            std :: cout << i << std :: endl;

        size_t cursor = i % 16;
        data :: hashtable <bytewise :: buffer, uint16_t> shortcuts;

        network :: dns :: dump :: name(message, cursor, shortcuts, "net.google.it");
        network :: dns :: dump :: name(message, cursor, shortcuts, "net.google.it");
    }
}

#endif
