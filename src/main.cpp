#ifdef __main__

#include <iostream>
#include <unistd.h>
#include <thread>

#include "chrono/crontab.h"
#include "async/async.h"

promise <void> f(size_t id)
{
    $
    (
        static chrono :: crontab my_crontab;

        while(true)
        {
            $await(my_crontab.wait(rand() % 1000000));
            std :: cout << "Hello from " << id << std :: endl;
        }

        $return();
    );
}

int main()
{
    for(size_t i = 0; i < 1024; i++)
        f(i);

    while(true)
        usleep(1.e6);
}

#endif
