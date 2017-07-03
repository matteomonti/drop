#ifdef __main__

#include <iostream>
#include <type_traits>
#include <string>
#include <iomanip>

#include "utils/template/is_callable.h"

int main()
{
    auto lambda = [](const auto &)
    {
    };

    std :: cout << utils :: is_callable <decltype(lambda), const int> :: direct << std :: endl;
    std :: cout << utils :: is_callable <decltype(lambda), const int> :: value << std :: endl;
}

#endif
