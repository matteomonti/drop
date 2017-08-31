// Forward declarations includes

#include "types.h"

// Forward declarations

namespace network
{
    namespace dns
    {
        class record_base;
        template <qtype> class record;
    };
};

#if !defined(__forward__) && !defined(__drop__network__dns__record__h)
#define __drop__network__dns__record__h

// Libraries

#include <stdint.h>

// Includes

#include "types.h"
#include "name.h"
#include "network/address.h"
#include "bitmask.h"
#include "string.h"

namespace network :: dns
{
    class record_base
    {
        // Friends

        template <qtype> friend class record;

        // Members

        name _name;
        qclass _qclass;
        uint32_t _ttl;

        // Private constructors

        record_base(const name &, const qclass &, const uint32_t &);

    public:

        // Getters

        const name & name() const;
        const qclass & qclass() const;
        const uint32_t & ttl() const;
    };

    template <> class record <A> : public record_base
    {
        // Members

        class address :: ip _address;

    public:

        // Constructors

        record(const class name &, const enum qclass &, const uint32_t &, const class address :: ip &);

        // Getters

        const class address :: ip & address() const;
    };

    template <> class record <NS> : public record_base
    {
        // Members

        class name _nameserver;

    public:

        // Constructors

        record(const class name &, const enum qclass &, const uint32_t &, const class name &);

        // Getters

        const class name & nameserver() const;
    };

    template <> class record <CNAME> : public record_base
    {
        // Members

        class name _cname;

    public:

        // Constructors

        record(const class name &, const enum qclass &, const uint32_t &, const class name &);

        // Getters

        const class name & cname() const;
    };

    template <> class record <SOA> : public record_base
    {
        // Members

        class name _mname;
        class name _rname;

        uint32_t _serial;
        uint32_t _refresh;
        uint32_t _retry;
        uint32_t _expire;
        uint32_t _minimum;

    public:

        // Constructors

        record(const class name &, const enum qclass &, const uint32_t &, const class name &, const class name &, const uint32_t &, const uint32_t &, const uint32_t &, const uint32_t &, const uint32_t &);

        // Getters

        const class name & mname() const;
        const class name & rname() const;

        const uint32_t & serial() const;
        const uint32_t & refresh() const;
        const uint32_t & retry() const;
        const uint32_t & expire() const;
        const uint32_t & minimum() const;
    };

    template <> class record <WKS> : public record_base
    {
        // Members

        class address :: ip _address;
        protocol _protocol;
        bitmask _bitmask;

    public:

        // Constructors

        record(const class name &, const enum qclass &, const uint32_t &, const class address :: ip &, const protocol &, const bitmask &);

        // Getters

        const class address :: ip & address() const;
        const protocol & protocol() const;
        const bitmask & bitmask() const;
    };

    template <> class record <PTR> : public record_base
    {
        // Members

        class name _pointer;

    public:

        // Constructors

        record(const class name &, const enum qclass &, const uint32_t &, const class name &);

        // Getters

        const class name & pointer() const;
    };

    template <> class record <HINFO> : public record_base
    {
        // Members

        string _cpu;
        string _os;

    public:

        // Constructors

        record(const class name &, const enum qclass &, const uint32_t &, const string &, const string &);

        // Getters

        const string & cpu() const;
        const string & os() const;
    };

    template <> class record <MINFO> : public record_base
    {
        // Members

        class name _rmailbox;
        class name _emailbox;

    public:

        // Constructors

        record(const class name &, const enum qclass &, const uint32_t &, const class name &, const class name &);

        // Getters

        const class name & rmailbox() const;
        const class name & emailbox() const;
    };

    template <> class record <MX> : public record_base
    {
        // Members

        uint16_t _preference;
        class name _exchange;

    public:

        // Constructors

        record(const class name &, const enum qclass &, const uint32_t &, const uint16_t &, const class name &);

        // Getters

        const uint16_t & preference() const;
        const class name & exchange() const;
    };

    template <> class record <TXT> : public record_base
    {
    public:

        // Settings

        struct settings
        {
            static constexpr size_t max_texts = 16;
        };

    private:

        // Members

        string _texts[settings :: max_texts];
        size_t _count;

public:

        // Constructors

        record(const class name &, const enum qclass &, const uint32_t &, const string *, const size_t &);

        // Getters

        const size_t & count() const;

        // Operators

        const string & operator [] (const size_t &) const;
    };

    template <> class record <null>
    {
    };
};

#endif
