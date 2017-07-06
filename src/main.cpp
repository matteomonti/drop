#ifdef __main__

#include <iostream>
#include <math.h>

#include "async/promise.hpp"

int main()
{
    promise <int> my_int_promise;
    promise <double> my_double_promise;
    promise <const char *> my_string_promise;

    promise <double> my_pi_promise;
    my_pi_promise.resolve(M_PI);

    my_double_promise.then([&](const double & value)
    {
        std :: cout << "First of all, double promise: " << value << std :: endl;
        return my_string_promise;
    }).then([&](const char * value)
    {
        std :: cout << "My string promise says: " << value << std :: endl;
        return my_pi_promise;
    }).then([](const double & value)
    {
        std :: cout << "My pi promise was already solved, but now I can say it: " << value << std :: endl;
    });

    promise <double> temporary_promise = my_int_promise.then([&](const int & value)
    {
        std :: cout << "Int promise solved with " << value << std :: endl;

        my_double_promise.then([](const double & value)
        {
            std :: cout << "Partial double promise solved with " << value << std :: endl;
        });

        return my_double_promise;
    });

    temporary_promise.then([](const double & value)
    {
        std :: cout << "Double promise solved with " << value << std :: endl;
    });

    my_int_promise.resolve(55);
    my_double_promise.resolve(32.22);

    temporary_promise.then([](const double & value)
    {
        std :: cout << "This is such a dumb callback, but still " << value << std :: endl;
    });

    my_string_promise.resolve("Hello World!");
}

#endif
