// Forward declarations

namespace network
{
    class connection;
};

#if !defined(__forward__) && !defined(__drop__network__connection__h)
#define __drop__network__connection__h

// Libraries

#include <memory>
#include <type_traits>

// Includes

#include "data/variant.hpp"
#include "sockets/tcp.h"
#include "utils/template/enable_in.h"
#include "bytewise/bytewise.h"
#include "bytewise/bsize.h"

namespace network
{
    class connection
    {
        // Service nested classes

        class arc
        {
            // Members

            data :: variant <sockets :: tcp> _socket;

            struct
            {
                bytewise :: buffer buffer;
                size_t size;
                size_t cursor;
            } _write;

            struct
            {
                struct
                {
                    char size[sizeof(uint32_t)];
                    bytewise :: buffer data;
                } buffer;

                size_t size;
                size_t cursor;
            } _read;

        public:

            // Constructors

            template <typename type> arc(const type &);

            // Destructor

            ~arc();

            // Methods

            void send(const bytewise :: buffer &);
            template <typename type, std :: enable_if_t <bytewise :: traits <type> :: enabled && (bytewise :: traits <type> :: size > 0)> * = nullptr> void send(const type &);
            template <typename type, std :: enable_if_t <bytewise :: traits <type> :: enabled && (bytewise :: traits <type> :: size == 0)> * = nullptr> void send(const type &);

            template <typename type, std :: enable_if_t <std :: is_same <type, bytewise :: buffer> :: value> * = nullptr> type receive();
            template <typename type, std :: enable_if_t <bytewise :: traits <type> :: enabled && (bytewise :: traits <type> :: size > 0)> * = nullptr> type receive();
            template <typename type, std :: enable_if_t <bytewise :: traits <type> :: enabled && (bytewise :: traits <type> :: size == 0)> * = nullptr> type receive();

        private:

            // Private methods

            void receive_setup(const size_t & = 0);
            bool receive_step();
            template <typename type, std :: enable_if_t <(bytewise :: traits <type> :: size > 0)> * = nullptr> type receive_finalize();
            template <typename type, std :: enable_if_t <(bytewise :: traits <type> :: size == 0)> *  = nullptr> type receive_finalize();
        };

        // Members

        std :: shared_ptr <arc> _arc;

    public:

        // Constructors

        template <typename type, utils :: enable_in_t <type, sockets :: tcp> * = nullptr> connection(const type &);

        // Methods

        template <typename type, std :: enable_if_t <bytewise :: traits <type> :: enabled || std :: is_same <type, bytewise :: buffer> :: value> * = nullptr> void send(const type &);
        template <typename type, std :: enable_if_t <bytewise :: traits <type> :: enabled || std :: is_same <type, bytewise :: buffer> :: value> * = nullptr> type receive();
    };
};

#endif
