// Forward declarations

namespace utils
{
    template <typename type> class pnew;
};

#if !defined(__forward__) && !defined(__drop__utils__misc__pnew__h)
#define __drop__utils__misc__pnew__h

// Libraries

#include <type_traits>
#include <stddef.h>

namespace utils
{
    template <typename type> class pnew
    {
    public:

        // Nested classes

        class item
        {
            // Friends

            template <typename> friend class pnew;

            // Members

            std :: aligned_storage_t <sizeof(type), alignof(type)> * _item;

            // Constructors

            item(std :: aligned_storage_t <sizeof(type), alignof(type)> &);

        public:

            // Operators

            template <typename... atypes, std :: enable_if_t <std :: is_constructible <type, atypes...> :: value> * = nullptr> void operator () (atypes && ...);
        };

    private:

        // Members

        std :: aligned_storage_t <sizeof(type), alignof(type)> * _items;

    public:

        // Constructors

        pnew(const size_t &);

        // Operators

        item operator [] (const size_t &);

        // Casting

        operator type * ();
    };
};

#endif
