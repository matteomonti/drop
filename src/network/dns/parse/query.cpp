// Includes

#include "query.h"

namespace network :: dns :: parse
{
    // Functions

    data :: variant <:: network :: dns :: query <A>, :: network :: dns :: query <NS>, :: network :: dns :: query <CNAME>, :: network :: dns :: query <SOA>, :: network :: dns :: query <WKS>, :: network :: dns :: query <PTR>, :: network :: dns :: query <HINFO>, :: network :: dns :: query <MINFO>, :: network :: dns :: query <MX>, :: network :: dns :: query <TXT>, :: network :: dns :: query <null>> query(const char * message, const size_t & size, size_t & cursor)
    {
        typedef data :: variant <:: network :: dns :: query <A>, :: network :: dns :: query <NS>, :: network :: dns :: query <CNAME>, :: network :: dns :: query <SOA>, :: network :: dns :: query <WKS>, :: network :: dns :: query <PTR>, :: network :: dns :: query <HINFO>, :: network :: dns :: query <MINFO>, :: network :: dns :: query <MX>, :: network :: dns :: query <TXT>, :: network :: dns :: query <null>> variant;

        mask mask{.size = 0};
        bool success = parse :: name(mask, message, size, cursor);

        if(!success)
            return variant :: construct <:: network :: dns :: query <null>> ();

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

        if(cursor + 4 > size)
            return variant :: construct <:: network :: dns :: query <null>> ();

        uint16_t qtype = ntohs(reinterpret_cast <const uint16_t &> (message[cursor]));
        uint16_t qclass = ntohs(reinterpret_cast <const uint16_t &> (message[cursor + 2]));

        cursor += 4;

        char name[256];
        size_t nsize = 0;

        for(size_t i = 0; i < mask.size; i++)
        {
            if(i > 0)
                name[nsize++] = '.';

            memcpy(name + nsize, message + mask.labels[i].beg, (mask.labels[i].end - mask.labels[i].beg));
            nsize += (mask.labels[i].end - mask.labels[i].beg);
        }

        switch(qtype)
        {
            case 1:
                return variant :: construct <:: network :: dns :: query <A>> (name, nsize, static_cast <enum qclass> (qclass));
            case 2:
                return variant :: construct <:: network :: dns :: query <NS>> (name, nsize, static_cast <enum qclass> (qclass));
            case 5:
                return variant :: construct <:: network :: dns :: query <CNAME>> (name, nsize, static_cast <enum qclass> (qclass));
            case 6:
                return variant :: construct <:: network :: dns :: query <SOA>> (name, nsize, static_cast <enum qclass> (qclass));
            case 11:
                return variant :: construct <:: network :: dns :: query <WKS>> (name, nsize, static_cast <enum qclass> (qclass));
            case 12:
                return variant :: construct <:: network :: dns :: query <PTR>> (name, nsize, static_cast <enum qclass> (qclass));
            case 13:
                return variant :: construct <:: network :: dns :: query <HINFO>> (name, nsize, static_cast <enum qclass> (qclass));
            case 14:
                return variant :: construct <:: network :: dns :: query <MINFO>> (name, nsize, static_cast <enum qclass> (qclass));
            case 15:
                return variant :: construct <:: network :: dns :: query <MX>> (name, nsize, static_cast <enum qclass> (qclass));
            case 16:
                return variant :: construct <:: network :: dns :: query <TXT>> (name, nsize, static_cast <enum qclass> (qclass));
            default:
                return variant :: construct <:: network :: dns :: query <null>> ();
        };

        return variant :: construct <:: network :: dns :: query <null>> ();
    }
};
