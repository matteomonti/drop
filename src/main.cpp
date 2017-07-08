#ifdef __main__

#include <iostream>
#include <math.h>

#include "async/context.hpp"

int main()
{
    promise <int> my_int_promise;
    int my_int;

    async :: contextualize <void> ([&](auto & context)
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
                return context.resolve();
        };
    }).then([]()
    {
        std :: cout << "Context resolved." << std :: endl;
    });

    my_int_promise.resolve(55);
}

#endif
