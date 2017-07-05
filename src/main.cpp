#ifdef __main__

#include <iostream>

#include "data/optional.hpp"

class myclass
{
public:

    myclass(const int &, double &, const char *)
    {
        std :: cout << "Myclass constructor" << std :: endl;
    }

    myclass(const myclass &)
    {
        std :: cout << "Myclass constructor" << std :: endl;
    }

    myclass(myclass &&) = delete;

    ~myclass()
    {
        std :: cout << "Myclass destructor" << std :: endl;
    }

    myclass & operator = (const myclass &) = default;
    myclass & operator = (myclass &&) = delete;


    void f()
    {
        std :: cout << "Hi there!" << std :: endl;
    }
};

int main()
{
    double d = 4.44;
    data :: optional <myclass> x(3, d, "hello");
    data :: optional <myclass> y = x;
    data :: optional <myclass> z = std :: move(y);

    z = x;
    x = std :: move(y);

    x = data :: null;

    if(x)
        std :: cout << "Something is wrong" << std :: endl;
}

#endif
