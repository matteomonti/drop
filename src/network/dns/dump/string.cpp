// Includes

#include "string.h"

namespace network :: dns :: dump
{
    // Functions
    
    void string(char * message, size_t & cursor, const :: network :: dns :: string & string)
    {
        reinterpret_cast <uint8_t &> (message[cursor++]) = string.length();
        memcpy(&(message[cursor]), string, string.length());

        cursor += string.length();
    }
};
