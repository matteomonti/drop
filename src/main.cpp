#ifdef __main__

#include <iostream>
#include <math.h>

#include "async/context.hpp"

int main()
{
    auto my_context = async :: contextualize <double> ([](auto & context)
    {
        switch(context.entrypoint())
        {
            default:
                assert(false);
            case 0:;
                std :: cout << "First run" << std :: endl;
                return context.leave(1);
            case 1:;
                std :: cout << "Second run" << std :: endl;
                return context.resolve(44.3);
        };
    });

    my_context->promise().then([](const double & value)
    {
        std :: cout << "Context resolved: " << value << std :: endl;
    });

    my_context->run();
    my_context->run();
}

#endif
