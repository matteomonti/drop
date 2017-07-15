// Forward declarations

namespace thread
{
    template <typename> class channel;
};

#if !defined(__forward__) && !defined(__drop__thread__channel__h)
#define __drop__thread__channel__h

// Libraries

#include <stddef.h>
#include <type_traits>
#include <exception>

// Includes

#include "data/optional.hpp"

namespace thread
{
    template <typename type> class channel // TODO: Manage constructors for _buffer entries! Otherwise objects that were never instantiated will be assigned with undefined behavior.
    {
        // Settings

        struct settings
        {
            static constexpr size_t base_chunk_alloc = 1024;
        };

        // Service nested classes

        class chunk
        {
            // Members

            volatile std :: aligned_storage_t <sizeof(type), alignof(type)> * _buffer;
            size_t _size;

            struct
            {
                volatile size_t write;
                volatile size_t read;
            } _cursor;

            volatile chunk * _next;
            volatile size_t _last;

        public:

            // Constructors

            chunk(const size_t &);

            // Destructors

            ~chunk();

            // Methods

            void push(const type &);
            data :: optional <type> pop();
        };

        // Members

        chunk * _read;
        chunk * _write;

    public:

        // Constructors

        channel();

        // Methods

        void push(const type &);
        data :: optional <type> pop();
    };
};

#endif
