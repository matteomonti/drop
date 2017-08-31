#ifdef __main__

#include <iostream>

#include "network/dns/dump/record.hpp"

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

    network :: dns :: string strings[] = {"asd", "lol", "lmfao"};
    network :: dns :: record <network :: dns :: TXT> my_record("google.it", network :: dns :: internet, 3600, strings, 3);
    network :: dns :: dump :: record(message, cursor, shortcuts, my_record);

    print(message, cursor);
}

#endif
