#ifdef __main__

#include <iostream>
#include <unistd.h>
#include <thread>

#include "chrono/timelock.hpp"

int main()
{
    chrono :: timelock <const char *> my_timelock;

    my_timelock.push("Ladies and gentleman...", microtime() + 5.e6);
    my_timelock.push("This is the story...", microtime() + 8.e6);
    my_timelock.push("of", microtime() + 12.e6);
    my_timelock.push("my", microtime() + 13.e6);
    my_timelock.push("life.", microtime() + 14.e6);

    while(true)
    {
        data :: optional <const char *> value = my_timelock.pop();

        if(value)
            std :: cout << *value << std :: endl;
    }
}

#endif
