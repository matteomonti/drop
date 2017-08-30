#ifdef __main__

#include <iostream>

#include "data/hashtable.hpp"

int main()
{
    data :: hashtable <bytewise :: buffer, bytewise :: buffer> my_hashtable;

    my_hashtable.add("Sherlock", "Holmes");
    my_hashtable.add("John", "Watson");
    my_hashtable.add("James", "Moriarty");

    std :: cout << *my_hashtable["Sherlock"] << std :: endl;
    std :: cout << *my_hashtable["John"] << std :: endl;
    std :: cout << *my_hashtable["James"] << std :: endl;
}

#endif
