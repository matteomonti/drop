#ifdef __main__

#include <iostream>

#include "async/promise.hpp"

int main()
{
    auto lambda = [](const int & value)
    {
        std :: cout << "Value: " << value << std :: endl;
    };

    promise <int> :: callback <decltype(lambda)> callback(lambda);
    promise <int> :: arc arc;
    arc._value = 99;
    callback.run(arc);
}

#endif
