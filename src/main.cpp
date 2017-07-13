#ifdef __main__

#include <iostream>
#include <unistd.h>
#include <thread>

#include "thread/channel.hpp"

thread :: channel <int> channel;

void sender()
{
    for(size_t i = 0;; i++)
        channel.push(i);
}

void receiver()
{
    while(true)
    {
        while(data :: optional <int> value = channel.pop())
            if(value && *value % 1000000 == 0)
                std :: cout << *value << std :: endl;
    }
}

int main()
{
    std :: thread sender_thread(sender);
    std :: thread receiver_thread(receiver);

    sender_thread.join();
    receiver_thread.join();
}

#endif
