#ifdef __main__

#include <iostream>
#include <math.h>

#include "async/contextualizer.hpp"
#include "async/leaver.hpp"
#include "async/macros.h"

promise <int> my_int_promise;
int my_int;

promise <int> int_tomorrow()
{
    async
    (
        std :: cout << "First run" << std :: endl;
        await(my_int) = my_int_promise;
        std :: cout << "Second run" << std :: endl;
        return context.resolve(22);
    );
}

int main()
{
    int_tomorrow().then([](const int & value)
    {
        std :: cout << "Context resolved with " << value << std :: endl;
    });

    my_int_promise.resolve(55);
}

#endif
