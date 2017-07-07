#ifdef __main__

#include <iostream>
#include <math.h>

#include "async/context.hpp"

int main()
{
    auto my_context = async :: contextualize([](auto & context)
    {
        std :: cout << "Hello there!" << std :: endl;
    });

    my_context->run();
}

#endif
