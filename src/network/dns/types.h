// Forward declarations

namespace network
{
    namespace dns
    {
        class A;
        class NS;
        class CNAME;
        class SOA;
        class WKS;
        class PTR;
        class HINFO;
        class MINFO;
        class MX;
        class TXT;

        class null;
    };
};

#if !defined(__forward__) && !defined(__drop__network__dns__types__h)
#define __drop__network__dns__types__h

namespace network :: dns
{
    enum qclass {internet = 1, chaos = 3, hesiod = 4};
};

#endif
