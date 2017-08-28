// Includes

#include "query.h"

namespace network :: dns :: parse
{
    // Functions

    data :: variant <:: network :: dns :: query <A>, :: network :: dns :: query <NS>, :: network :: dns :: query <CNAME>, :: network :: dns :: query <SOA>, :: network :: dns :: query <WKS>, :: network :: dns :: query <PTR>, :: network :: dns :: query <HINFO>, :: network :: dns :: query <MINFO>, :: network :: dns :: query <MX>, :: network :: dns :: query <TXT>, :: network :: dns :: query <null>> query(const char * message, const size_t & size, size_t & cursor)
    {
        typedef data :: variant <:: network :: dns :: query <A>, :: network :: dns :: query <NS>, :: network :: dns :: query <CNAME>, :: network :: dns :: query <SOA>, :: network :: dns :: query <WKS>, :: network :: dns :: query <PTR>, :: network :: dns :: query <HINFO>, :: network :: dns :: query <MINFO>, :: network :: dns :: query <MX>, :: network :: dns :: query <TXT>, :: network :: dns :: query <null>> variant;

        data :: optional <class name> name = parse :: name(message, size, cursor);

        if(!name)
            return variant :: construct <:: network :: dns :: query <null>> ();

        if(cursor + 4 > size)
            return variant :: construct <:: network :: dns :: query <null>> ();

        uint16_t qtype = ntohs(reinterpret_cast <const uint16_t &> (message[cursor]));
        uint16_t qclass = ntohs(reinterpret_cast <const uint16_t &> (message[cursor + 2]));

        cursor += 4;

        switch(qtype)
        {
            case 1:
                return variant :: construct <:: network :: dns :: query <A>> (*name, static_cast <enum qclass> (qclass));
            case 2:
                return variant :: construct <:: network :: dns :: query <NS>> (*name, static_cast <enum qclass> (qclass));
            case 5:
                return variant :: construct <:: network :: dns :: query <CNAME>> (*name, static_cast <enum qclass> (qclass));
            case 6:
                return variant :: construct <:: network :: dns :: query <SOA>> (*name, static_cast <enum qclass> (qclass));
            case 11:
                return variant :: construct <:: network :: dns :: query <WKS>> (*name, static_cast <enum qclass> (qclass));
            case 12:
                return variant :: construct <:: network :: dns :: query <PTR>> (*name, static_cast <enum qclass> (qclass));
            case 13:
                return variant :: construct <:: network :: dns :: query <HINFO>> (*name, static_cast <enum qclass> (qclass));
            case 14:
                return variant :: construct <:: network :: dns :: query <MINFO>> (*name, static_cast <enum qclass> (qclass));
            case 15:
                return variant :: construct <:: network :: dns :: query <MX>> (*name, static_cast <enum qclass> (qclass));
            case 16:
                return variant :: construct <:: network :: dns :: query <TXT>> (*name, static_cast <enum qclass> (qclass));
            default:
                return variant :: construct <:: network :: dns :: query <null>> ();
        };

        return variant :: construct <:: network :: dns :: query <null>> ();
    }
};
