#ifdef __main__

#include <iostream>
#include <unistd.h>
#include <thread>

#include "thread/semaphore.h"

thread :: semaphore sema(1), semb;

void a()
{
    while(true)
    {
        sema.wait();
        std :: cout << "Hello ";
        semb.post();
    }
}

void b()
{
    while(true)
    {
        semb.wait();
        std :: cout << "World!" << std :: endl;
        sema.post();
    }
}

int main()
{
    std :: thread ta(a), tb(b);

    ta.join();
    tb.join();
}

#endif
