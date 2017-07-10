#ifdef __main__

#include <iostream>
#include <math.h>

#include "async/async.h"

int main()
{
    promise <int> my_promise;
    my_promise.then([](const int & value)
    {
        std :: cout << value << std :: endl;
    });

    my_promise.resolve(559);
}

#endif
