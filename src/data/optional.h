// Forward declarations

namespace data
{
    template <typename> class optional_base;
    template <typename> class optional;
    class null;
};

#if !defined(__forward__) && !defined(__drop__data__optional__h)
#define __drop__data__optional__h

// Libraries

#include <type_traits>
#include <assert.h>

// Includes

#include "utils/misc/copy_constructible.h"
#include "utils/misc/move_constructible.h"
#include "utils/misc/copy_assignable.h"
#include "utils/misc/move_assignable.h"

namespace data
{
    template <typename type> class optional_base
    {
        // Members

        bool _exists;
        std :: aligned_storage_t <sizeof(type), alignof(type)> _bytes;

    public:

        // Constructors

        optional_base(null);
        template <typename... types, std :: enable_if_t <std :: is_constructible <type, types...> :: value> * = nullptr> optional_base(types && ...);
        optional_base(const optional_base &);
        optional_base(optional_base &&);

        // Destructor

        ~optional_base();

        // Operators

        type & operator * ();
        const type & operator * () const;

        type * operator -> ();
        const type * operator -> () const;

        optional_base & operator = (const optional_base &);
        optional_base & operator = (optional_base &&);

        // Casting

        operator const bool & () const;
    };

    template <typename type> class optional : public optional_base <type>,
                                              public utils :: copy_constructible <std :: is_copy_constructible <type> :: value>,
                                              public utils :: move_constructible <std :: is_move_constructible <type> :: value>,
                                              public utils :: copy_assignable <std :: is_copy_constructible <type> :: value && std :: is_copy_assignable <type> :: value>,
                                              public utils :: move_assignable <std :: is_move_constructible <type> :: value && std :: is_move_assignable <type> :: value>
    {
    public:

        // Constructors

        optional(null);
        template <typename... types, std :: enable_if_t <std :: is_constructible <type, types...> :: value> * = nullptr> optional(types && ...);
    };

    class null
    {
    };

    extern null null;
};

#endif
