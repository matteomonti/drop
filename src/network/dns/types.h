// Forward declarations

namespace network
{
    namespace dns
    {
    };
};

#if !defined(__forward__) && !defined(__drop__network__dns__types__h)
#define __drop__network__dns__types__h

namespace network :: dns
{
    enum qtype {A = 1, NS = 2, CNAME = 5, SOA = 6, WKS = 11, PTR = 12, HINFO = 13, MINFO = 14, MX = 15, TXT = 16, null = 0};
    enum qclass {internet = 1, chaos = 3, hesiod = 4};
    enum protocol {ICMP = 1, IGMP = 2, GGP = 3, ST = 5, TCP = 6, UCL = 7, EGP = 8, IGP = 9, BNN_RCC_MON = 10, NVP_II = 11, PUP = 12, ARGUS = 13, EMCON = 14, XNET = 15, CHAOS = 16, UDP = 17, MUX = 18, DCN_MEAS = 19, HMP = 20, PRM = 21, XNS_IDP = 22, TRUNK_1 = 23, TRUNK_2 = 24, LEAF_1 = 25, LEAF_2 = 26, RDP = 27, IRTP = 28, ISO_TP4 = 29, NETBLT = 30, MFE_NSP = 31, MERIT_INP = 32, SEP = 33, CFTP = 62, SAT_EXPAK = 64, MIT_SUBNET = 65, RVD = 66, IPPC = 67, SAT_MON = 69, IPCV = 71, BR_SAT_MON = 76, WB_MON = 78, WB_EXPAK = 79};
};

#endif
