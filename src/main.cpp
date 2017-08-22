#ifdef __main__

#include <iostream>
#include <unistd.h>
#include <thread>

#include "utils/template/function.hpp"

int main()
{
    utils :: function <int (int)> f([](int x)
    {
        return 2 * x;
    });

    f = [](int x)
    {
        return 3 * x;
    };

    std :: cout << f(2) << std :: endl;
    f.release();
}

#endif
