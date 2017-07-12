#ifdef __main__

#include <iostream>
#include <math.h>

#include "async/async.h"

promise <int> my_int_promise;

promise <int> get_rand()
{
    my_int_promise = promise <int> ();
    return my_int_promise;
}

promise <void> f()
{
    int i;
    int j;

    async
    (
        for(i = 0; i < 1000; i++)
        {
            await(j) = get_rand();
            std :: cout << j << std :: endl;
        }

        return context.resolve();
    );
}

int main()
{
    f().then([]()
    {
        std :: cout << "F completed" << std :: endl;
    });

    for(int i = 0; i < 1000; i++)
        my_int_promise.resolve(rand());
}

#endif
