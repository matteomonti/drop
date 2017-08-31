#ifdef __main__

#include <iostream>

#include "network/dns/dump/query.hpp"

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

    network :: dns :: query <network :: dns :: A> my_query("google.it", network :: dns :: internet);

    network :: dns :: dump :: query(message, cursor, shortcuts, my_query);
    print(message, cursor);
}

#endif
