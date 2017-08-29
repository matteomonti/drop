// Includes

#include "string.h"

namespace network :: dns :: parse
{
    data :: optional <:: network :: dns :: string> string(const char * message, const size_t & size, size_t & cursor)
    {
        if(size == cursor)
            return data :: null;

        uint8_t length = reinterpret_cast <const uint8_t &> (message[cursor]);
        cursor++;

        if(cursor + length > size)
            return data :: null;

        :: network :: dns :: string string(&(message[cursor]), length);
        cursor += length;

        return string;
    }
};
