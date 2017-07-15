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
    no_default_constructor * v = utils :: pnew <no_default_constructor> :: uniform [1024] (333);

    for(size_t i = 0; i < 1024; i++)
        std :: cout << v[i].i << std :: endl;
}

#endif
