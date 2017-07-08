#ifdef __main__

#include <iostream>
#include <math.h>

#include "async/contextualizer.hpp"

promise <int> my_int_promise;
int my_int;

promise <int> int_tomorrow()
{
    return async :: contextualize([&](auto & context)
    {
        switch(context.entrypoint())
        {
            default:
                assert(false);
            case 0:;
                std :: cout << "First run" << std :: endl;
                return context.leave(1, my_int, my_int_promise);
            case 1:;
                std :: cout << "Second run" << std :: endl;
                return context.resolve(22);
        };
    });
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
