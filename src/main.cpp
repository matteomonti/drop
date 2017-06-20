#ifdef __main__

#include <iostream>
#include <type_traits>
#include <string>

#include "bytewise/macros.h"
#include "bytewise/visitors/arithmetic.hpp"

struct myotherclass
{
    // Self

    typedef myotherclass self;

    // Members

    int a;
    int b;

    // Bytewise

    bytewise(a);
    bytewise(b);
};

struct myclass
{
    // Self

    typedef myclass self;

    // Members

    int x[4];
    double y;
    myotherclass m;
    char q[16];

    // Bytewise

    bytewise(x);
    bytewise(y);
    bytewise(m);
    bytewise(q);
};

template <size_t alloc> class myvisitor
{
    // Members

    char _bytes[alloc];
    size_t _read_cursor;
    size_t _write_cursor;

public:

    myvisitor() : _read_cursor(0), _write_cursor(0)
    {
    }

    template <size_t size> void read(const char (&value) [size])
    {
        std :: cout << "Received " << size << " bytes." << std :: endl;
        memcpy(this->_bytes + this->_read_cursor, value, size);
        this->_read_cursor += size;
    }

    template <size_t size> void write(char (&value) [size])
    {
        std :: cout << "Sending " << size << " bytes." << std :: endl;
        memcpy(value, this->_bytes + this->_write_cursor, size);

        this->_write_cursor += size;
    }
};

int main()
{
    using namespace bytewise;

    myclass myobj;

    myobj.x[0] = 0;
    myobj.x[1] = 1;
    myobj.x[2] = 2;
    myobj.x[3] = 3;
    myobj.y = 4.5;
    myobj.m.a = 6;
    myobj.m.b = 7;
    strcpy(myobj.q, "eight and so on");

    myvisitor <scanners :: arithmetic <myclass> :: type :: size> visitor;
    visitors :: arithmetic <myclass> :: read(myobj, visitor);

    myclass myotherobj;
    visitors :: arithmetic <myclass> :: write(myotherobj, visitor);

    std :: cout << myotherobj.x[0] << std :: endl;
    std :: cout << myotherobj.x[1] << std :: endl;
    std :: cout << myotherobj.x[2] << std :: endl;
    std :: cout << myotherobj.x[3] << std :: endl;
    std :: cout << myotherobj.y << std :: endl;
    std :: cout << myotherobj.m.a << std :: endl;
    std :: cout << myotherobj.m.b << std :: endl;
    std :: cout << myotherobj.q << std :: endl;
}

#endif
