#ifdef __main__

#include <iostream>
#include <math.h>

#include "async/promise.hpp"

int main()
{
    promise <double> my_double_promise;

    my_double_promise.then([](const double & value)
    {
        std :: cout << "Resolved with: " << value << std :: endl;
    }).except([](const std :: exception_ptr & exception)
    {
        std :: cout << "Rejected with error: ";

        try
        {
            std :: rethrow_exception(exception);
        }
        catch(const char * error)
        {
            std :: cout << error << std :: endl;
        }
    });

    // my_double_promise.resolve(4.44);
    my_double_promise.reject("Something went wrong.");
}

#endif
