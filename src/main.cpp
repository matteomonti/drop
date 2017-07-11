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
    // my_pi_promise.resolve(M_PI);

    my_double_promise.then([&](const double & value)
    {
        std :: cout << "First of all, double promise: " << value << std :: endl;
        return my_string_promise;
    }).then([&](const char * value)
    {
        std :: cout << "My string promise says: " << value << std :: endl;
        my_pi_promise.reject("Pi promise rejected. Don't like it.");
        return my_pi_promise;
    }).then([](const double & value)
    {
        std :: cout << "My pi promise was already solved, but now I can say it: " << value << std :: endl;
    }).except([](const std :: exception_ptr exception)
    {
        std :: cout << "Exception detected: ";

        try
        {
            std :: rethrow_exception(exception);
        }
        catch(const char * error)
        {
            std :: cout << error << std :: endl;
        }
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
    // my_double_promise.reject("Something went horribly wrong!");

    temporary_promise.then([](const double & value)
    {
        std :: cout << "This is such a dumb callback, but still " << value << std :: endl;
    });

    my_string_promise.resolve("Hello World!");


    promise <void> my_void_promise;
    promise <void> my_other_void_promise;
    promise <void> yet_another_void_promise;

    my_void_promise.then([&]()
    {
        std :: cout << "Promise solved!" << std :: endl;
        return my_other_void_promise;
    }).then([&]()
    {
        std :: cout << "Other promise solved!" << std :: endl;
        return yet_another_void_promise;
    }).then([]()
    {
        std :: cout << "Yet another promise resolved!" << std :: endl;
    });

    my_void_promise.resolve();
    my_other_void_promise.resolve();
    yet_another_void_promise.resolve();
}

#endif
