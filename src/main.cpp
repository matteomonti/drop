#ifdef __main__

#include <iostream>

#include "utils/misc/pnew.hpp"

class no_default_constructor
{
public:

    int i;

    no_default_constructor(int _i) : i(_i)
    {
    }
};

int main()
{
    utils :: pnew <no_default_constructor> x(1024);

    for(size_t i = 0; i < 1024; i++)
        x[i](i);

    no_default_constructor * v = x;

    for(size_t i = 0; i < 1024; i++)
        std :: cout << v[i].i << std :: endl;
}

#endif
