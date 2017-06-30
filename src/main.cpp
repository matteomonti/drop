#ifdef __main__

#include <iostream>
#include <type_traits>
#include <string>
#include <iomanip>

#include "utils/template/all.h"
#include "utils/misc/copiable.h"

int main()
{
    std :: cout << utils :: all <std :: is_copy_constructible, int, double, char, int, utils :: copiable <false>> :: value << std :: endl;
}

#endif
