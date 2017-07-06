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

    class callback_base;
    template <typename> class callback;
    class arc;

    // Service nested classes

    class callback_base
    {
    public:

        // Interface methods

        virtual void run(const arc &) = 0;
    };

    template <typename lambda> class callback : public callback_base
    {
        // Members

        lambda _callback;

    public:

        // Constructors

        callback(const lambda &);

        // Methods

        void run(const arc &);
    };

    class arc
    {
        // Members

        data :: optional <type> _value;
        callback_base * _callbacks[settings :: callbacks];

    public:

        // Constructors

        arc();

        // Getters

        const type & value() const;

        // Methods

        template <typename lambda> void then(const lambda &);
        void resolve(const type &);
    };

    // Members

    std :: shared_ptr <arc> _arc;

public:

    // Constructors

    promise();

    // Methods

    template <typename lambda, typename std :: enable_if_t <utils :: is_callable <lambda, const type &> :: value> * = nullptr> void then(const lambda &);
    void resolve(const type &);
};

#endif
