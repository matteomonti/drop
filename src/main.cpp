#ifdef __main__

#include <iostream>

#include "network/dns/dump/string.h"

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
    network :: dns :: dump :: string(message, cursor, "asd");
    network :: dns :: dump :: string(message, cursor, "lol");
    network :: dns :: dump :: string(message, cursor, "lmfao");
    network :: dns :: dump :: string(message, cursor, "xd");
    network :: dns :: dump :: string(message, cursor, "rotlmfao");
    network :: dns :: dump :: string(message, cursor, "ghghgh");

    print(message, cursor);
}

#endif
