// Includes

#include "name.h"

namespace network :: dns :: parse
{
    // Functions

    data :: optional <:: network :: dns :: name> name(const char * message, const size_t & size, size_t & cursor)
    {
        struct parser
        {
            static inline bool run(mask & mask, const char * message, const size_t & size, const size_t & entry)
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
                        return run(mask, message, entry, jump);
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

        mask mask{.size = 0};
        bool success = parser :: run(mask, message, size, cursor);

        if(!success)
            return data :: null;

        size_t label;

        for(label = 0; label < mask.size; label++)
        {
            if(mask.labels[label].beg == cursor + 1)
                cursor = mask.labels[label].end;
            else if(label < mask.size - 1)
            {
                cursor += 2;
                break;
            }
        }

        if(label == mask.size)
            cursor++;

        char name[256];
        size_t nsize = 0;

        for(size_t i = 0; i < mask.size; i++)
        {
            if(i > 0)
                name[nsize++] = '.';

            memcpy(name + nsize, message + mask.labels[i].beg, (mask.labels[i].end - mask.labels[i].beg));
            nsize += (mask.labels[i].end - mask.labels[i].beg);
        }

        return (class name){name, nsize};
    }
};
