#ifdef __main__

#include <iostream>

#include "async/promise.hpp"

int main()
{
    promise <int> my_int_promise;
    promise <double> my_double_promise;

    my_int_promise.then([&](const int & value)
    {
        std :: cout << "Int promise solved with " << value << std :: endl;

        my_double_promise.then([](const double & value)
        {
            std :: cout << "Partial double promise solved with " << value << std :: endl;
        });

        return my_double_promise;
    }).then([](const double & value)
    {
        std :: cout << "Double promise solved with " << value << std :: endl;
    });

    my_int_promise.resolve(55);
    my_double_promise.resolve(32.22);
}

#endif
