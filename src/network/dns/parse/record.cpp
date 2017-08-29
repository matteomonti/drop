// Includes

#include "record.h"

namespace network :: dns :: parse
{
    data :: variant <:: network :: dns :: record <A>, :: network :: dns :: record <NS>, :: network :: dns :: record <CNAME>, :: network :: dns :: record <SOA>, :: network :: dns :: record <WKS>, :: network :: dns :: record <PTR>, :: network :: dns :: record <HINFO>, :: network :: dns :: record <MINFO>, :: network :: dns :: record <MX>, :: network :: dns :: record <TXT>, :: network :: dns :: record <null>> record(const char * message, const size_t & size, size_t & cursor)
    {
        typedef data :: variant <:: network :: dns :: record <A>, :: network :: dns :: record <NS>, :: network :: dns :: record <CNAME>, :: network :: dns :: record <SOA>, :: network :: dns :: record <WKS>, :: network :: dns :: record <PTR>, :: network :: dns :: record <HINFO>, :: network :: dns :: record <MINFO>, :: network :: dns :: record <MX>, :: network :: dns :: record <TXT>, :: network :: dns :: record <null>> variant;

        data :: optional <class name> name = parse :: name(message, size, cursor);

        if(!name || cursor + 10 > size)
            return variant :: construct <:: network :: dns :: record <null>> ();

        uint16_t qtype = ntohs(reinterpret_cast <const uint16_t &> (message[cursor]));
        qclass qclass = static_cast <enum qclass> (ntohs(reinterpret_cast <const uint16_t &> (message[cursor + 2])));
        uint32_t ttl = ntohl(reinterpret_cast <const uint32_t &> (message[cursor + 4]));

        uint16_t length = ntohs(reinterpret_cast <const uint16_t &> (message[cursor + 8]));
        cursor += 10;

        switch(qtype)
        {
            case 1: // A
            {
                if(length < 4 || cursor + 4 > size)
                    return variant :: construct <:: network :: dns :: record <null>> ();

                class address :: ip address = reinterpret_cast <const class address :: ip &> (message[cursor]);

                cursor += length;
                return variant :: construct <:: network :: dns :: record <A>> (*name, qclass, ttl, address);
            }
            case 2: // NS
            {
                size_t rsize = cursor + length;
                data :: optional <class name> nameserver = parse :: name(message, rsize, cursor);

                if(!nameserver)
                    return variant :: construct <:: network :: dns :: record <null>> ();

                cursor = rsize;
                return variant :: construct <:: network :: dns :: record <NS>> (*name, qclass, ttl, *nameserver);
            }
            case 5: // CNAME
            {
                size_t rsize = cursor + length;
                data :: optional <class name> cname = parse :: name(message, rsize, cursor);

                if(!cname)
                    return variant :: construct <:: network :: dns :: record <null>> ();

                cursor = rsize;
                return variant :: construct <:: network :: dns :: record <CNAME>> (*name, qclass, ttl, *cname);
            }
            case 6: // SOA
            {
                size_t rsize = cursor + length;

                data :: optional <class name> mname = parse :: name(message, rsize, cursor);

                if(!mname)
                    return variant :: construct <:: network :: dns :: record <null>> ();

                data :: optional <class name> rname = parse :: name(message, rsize, cursor);

                if(!rname)
                    return variant :: construct <:: network :: dns :: record <null>> ();

                if(cursor + 20 > rsize)
                    return variant :: construct <:: network :: dns :: record <null>> ();

                uint32_t serial = ntohl(reinterpret_cast <const uint32_t &> (message[cursor]));
                uint32_t refresh = ntohl(reinterpret_cast <const uint32_t &> (message[cursor + 4]));
                uint32_t retry = ntohl(reinterpret_cast <const uint32_t &> (message[cursor + 8]));
                uint32_t expire = ntohl(reinterpret_cast <const uint32_t &> (message[cursor + 12]));
                uint32_t minimum = ntohl(reinterpret_cast <const uint32_t &> (message[cursor + 16]));

                cursor = rsize;
                return variant :: construct <:: network :: dns :: record <SOA>> (*name, qclass, ttl, *mname, *rname, serial, refresh, retry, expire, minimum);
            }
            case 11: // WKS
            {
                if(length < 5)
                    return variant :: construct <:: network :: dns :: record <null>> ();

                class address :: ip address = reinterpret_cast <const class address :: ip &> (message[cursor]);
                enum protocol protocol = static_cast <enum protocol> (reinterpret_cast <const uint8_t &> (message[cursor + 4]));

                bitmask bitmask(&(message[cursor + 5]), length - 5);

                cursor += length;
                return variant :: construct <:: network :: dns :: record <WKS>> (*name, qclass, ttl, address, protocol, bitmask);
            }
            case 12: // PTR
            {
                size_t rsize = cursor + length;
                data :: optional <class name> pointer = parse :: name(message, rsize, cursor);

                if(!pointer)
                    return variant :: construct <:: network :: dns :: record <null>> ();

                cursor = rsize;
                return variant :: construct <:: network :: dns :: record <PTR>> (*name, qclass, ttl, *pointer);
            }
            case 13: // HINFO
            {
                size_t rsize = cursor + length;
                data :: optional <class string> cpu = parse :: string(message, rsize, cursor);

                if(!cpu)
                    return variant :: construct <:: network :: dns :: record <null>> ();

                data :: optional <class string> os = parse :: string(message, rsize, cursor);

                if(!os)
                    return variant :: construct <:: network :: dns :: record <null>> ();

                cursor = rsize;
                return variant :: construct <:: network :: dns :: record <HINFO>> (*name, qclass, ttl, *cpu, *os);
            }
            case 14: // MINFO
            {
                size_t rsize = cursor + length;
                data :: optional <class name> rmailbox = parse :: name(message, rsize, cursor);

                if(!rmailbox)
                    return variant :: construct <:: network :: dns :: record <null>> ();

                data :: optional <class name> emailbox = parse :: name(message, rsize, cursor);

                if(!emailbox)
                    return variant :: construct <:: network :: dns :: record <null>> ();

                cursor = rsize;
                return variant :: construct <:: network :: dns :: record <MINFO>> (*name, qclass, ttl, *rmailbox, *emailbox);
            }
            case 15: // MX
            {
                if(length < 2)
                    return variant :: construct <:: network :: dns :: record <null>> ();

                uint16_t preference = ntohs(reinterpret_cast <const uint16_t &> (message[cursor]));

                size_t rsize = cursor + length;
                cursor += 2;

                data :: optional <class name> exchange = parse :: name(message, rsize, cursor);

                if(!exchange)
                    return variant :: construct <:: network :: dns :: record <null>> ();

                cursor = rsize;
                return variant :: construct <:: network :: dns :: record <MX>> (*name, qclass, ttl, preference, *exchange);
            }
            case 16: // TXT
            {
                size_t rsize = cursor + length;

                class string texts[:: network :: dns :: record <TXT> :: settings :: max_texts];

                size_t count;
                for(count = 0; count < :: network :: dns :: record <TXT> :: settings :: max_texts; count++)
                {
                    data :: optional <class string> text = parse :: string(message, rsize, cursor);

                    if(!text)
                        break;

                    texts[count] = *text;
                }

                if(!count)
                    return variant :: construct <:: network :: dns :: record <null>> ();

                return variant :: construct <:: network :: dns :: record <TXT>> (*name, qclass, ttl, texts, count);
            }
            default:
                return variant :: construct <:: network :: dns :: record <null>> ();
        };
    }
};
