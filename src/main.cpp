#ifdef __main__

#include <iostream>

#include "async/promise.hpp"

int main()
{
    promise <int> my_promise;

    my_promise.then([](const int & value)
    {
        std :: cout << "Promise solved with " << value << std :: endl;
    });

    my_promise.then([](const int & value)
    {
        std :: cout << "Promise also resolved with " << value << std :: endl;
    });

    my_promise.resolve(55);

    my_promise.then([](const int & value)
    {
        std :: cout << "Late then: " << value << std :: endl;
    });
}

#endif
