// Forward declarations

template <typename> class promise;

#if !defined(__forward__) && !defined(__drop__async__promise__h)
#define __drop__async__promise__h

// Libraries

#include <memory>
#include <type_traits>

// Includes

#include "data/optional.hpp"
#include "utils/template/is_callable.h"

template <typename type> class promise
{
public: // REMOVE ME

    // Settings

    struct settings
    {
        static constexpr size_t callbacks = 16;
    };

    // Friends

    template <typename> friend class promise;

    // Service nested classes forward declarations

    template <typename> struct is_promise;
    class callback_base;
    template <typename, bool> class callback;
    class arc;

    // Service nested classes

    template <typename> struct is_promise
    {
        static constexpr bool value = false;
    };

    template <typename ptype> struct is_promise <promise <ptype>>
    {
        static constexpr bool value = true;
    };

    class callback_base
    {
    public:

        // Destructor

        virtual ~callback_base();

        // Interface methods

        virtual void run(const type &) = 0;
    };

    template <typename lambda, bool = is_promise <std :: result_of_t <lambda(const type &)>> :: value> class callback;

    template <typename lambda> class callback <lambda, false> : public callback_base
    {
        // Members

        lambda _callback;

    public:

        // Constructors

        callback(const lambda &);

        // Getters

        void promise() const;

        // Methods

        void run(const type &);
    };

    template <typename lambda> class callback <lambda, true> : public callback_base
    {
        // Typedefs

        typedef std :: result_of_t <lambda(const type &)> chain;

        // Members

        lambda _callback;
        chain _promise;

    public:

        // Constructors

        callback(const lambda &);

        // Getters

        chain promise() const;

        // Methods

        void run(const type &);
    };

    class arc
    {
        // Members

        data :: optional <type> _value;
        callback_base * _callbacks[settings :: callbacks];
        std :: shared_ptr <arc> _alias;

    public:

        // Constructors

        arc();

        // Methods

        template <typename lambda> std :: conditional_t <is_promise <std :: result_of_t <lambda(const type &)>> :: value, std :: result_of_t <lambda(const type &)>, void> then(const lambda &);
        void alias(const promise &);
        void resolve(const type &);
    };

    // Members

    std :: shared_ptr <arc> _arc;

public:

    // Constructors

    promise();

    // Methods

    template <typename lambda, typename std :: enable_if_t <utils :: is_callable <lambda, const type &> :: value> * = nullptr> auto then(const lambda &);
    void resolve(const type &);

private:

    // Private methods

    void alias(const promise &);
};

#endif
