// Forward declarations

namespace data
{
    template <typename, typename> class hashtable;
};

#if !defined(__forward__) && !defined(__drop__data__hashtable__h)
#define __drop__data__hashtable__h

// Libraries

#include <stdint.h>
#include <stddef.h>
#include <type_traits>

// Includes

#include "optional.h"
#include "utils/template/is_callable.h"
#include "utils/misc/pnew.h"

namespace data
{
    template <typename ktype, typename vtype> class hashtable
    {
        // Settings

        struct settings
        {
            static constexpr size_t base_alloc = 32;
            static constexpr size_t expand_threshold = 2;
            static constexpr size_t contract_threshold = 8;
        };

        // Service nested classes

        struct entry
        {
            ktype key;
            vtype value;
        };

        // Members

        optional <entry> * _entries;
        size_t _size;
        size_t _alloc;

    public:

        // Constructors

        hashtable();

        // Destructor

        ~hashtable();

        // Methods

        void add(const ktype &, const vtype &);
        void remove(const ktype &);

        template <typename lambda, std :: enable_if_t <utils :: is_callable <lambda, const ktype &, const vtype &> :: value> * = nullptr> void each(const lambda &);

    private:

        // Private methods

        optional <size_t> slot(const ktype &) const;
        void realloc(const size_t &);

    public:

        // Operators

        optional <vtype> operator [] (const ktype &) const;

    private:

        // Private static methods

        template <typename type, std :: enable_if_t <std :: is_arithmetic <type> :: value && sizeof(type) == 4> * = nullptr> static size_t hash(const type &);
        template <typename type, std :: enable_if_t <std :: is_arithmetic <type> :: value && sizeof(type) == 8> * = nullptr> static size_t hash(const type &);
    };
};

#endif
