// Includes

#include "name.h"

namespace network :: dns :: parse
{
    // Functions
    
    bool name(mask & mask, const char * message, const size_t & size, const size_t & entry)
    {
        size_t cursor = entry;

        while(true)
        {
            if(cursor >= size)
                return false;

            uint8_t len = message[cursor];

            if(len == 0)
                return true;
            else if(len & 0xc0)
            {
                size_t jump = ntohs(reinterpret_cast <const uint16_t &> (message[cursor])) & 0x3ff;
                return name(mask, message, entry, jump);
            }
            else
            {
                if(cursor + len + 1 > size)
                    return false;
                else
                {
                    mask.labels[mask.size++] = {.beg = cursor + 1, .end = cursor + len + 1};
                    cursor += len + 1;
                }
            }
        }
    }
};
