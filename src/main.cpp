#ifdef __main__

#include <iostream>
#include <unistd.h>
#include <thread>

#include "thread/channel.hpp"

thread :: channel <size_t> my_channel;

void reader()
{
    size_t last = -1;

    while(true)
    {
        std :: cout << "Reading" << std :: endl;
        while(data :: optional <size_t> value = my_channel.pop())
        {
            assert(last + 1 == *value);
            last = *value;
            std :: cout << *value << std :: endl;
        }

        usleep(1.e7);
    }
}

void writer()
{
    for(size_t i = 0;; i++)
    {
        my_channel.push(i);
        usleep(rand() % 1000);
    }
}

int main()
{
    std :: thread reader_thread(reader);
    std :: thread writer_thread(writer);

    reader_thread.join();
    writer_thread.join();
}

#endif
