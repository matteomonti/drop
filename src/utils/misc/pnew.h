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
        // Service nested classes

        struct factories
        {
            class uniform
            {
                // Service nested classes

                class iterator
                {
                    // Friends

                    friend class uniform;
                    
                    // Constructors

                    pnew _pnew;
                    size_t _size;

                    // Constructors

                    iterator(const size_t &);

                public:

                    // Operators

                    template <typename... atypes, std :: enable_if_t <std :: is_constructible <type, atypes...> :: value> * = nullptr> const iterator & operator () (atypes && ...) const;

                    // Casting

                    operator type * () const;
                };

            public:

                // Operators

                iterator operator [] (const size_t &);
            };
        };

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

            template <typename... atypes, std :: enable_if_t <std :: is_constructible <type, atypes...> :: value> * = nullptr> void operator () (atypes && ...) const;
        };

    private:

        // Members

        std :: aligned_storage_t <sizeof(type), alignof(type)> * _items;

    public:

        // Constructors

        pnew(const size_t &);

        // Operators

        item operator [] (const size_t &) const;

        // Casting

        operator type * () const;

        // Static members

        static typename factories :: uniform uniform;
    };
};

#endif
