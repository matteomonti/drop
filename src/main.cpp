#ifdef __main__

#include <iostream>
#include <unistd.h>
#include <thread>

#include "bytewise/bytewise.h"

int main()
{
    char message[1024];
    bytewise :: buffer buffer(message, 1024, bytewise :: buffer :: reference);

    strcpy(buffer, "Hello World!");
    std :: cout << message << std :: endl;
}

#endif
