// Forward declarations

template <typename> class promise;

#if !defined(__forward__) && !defined(__drop__async__promise__h)
#define __drop__async__promise__h

// Libraries

#include <memory>
#include <type_traits>

// Includes

#include "data/optional.hpp"

template <typename type> class promise
{
public: // REMOVE ME

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

        // Methods

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
    public: // REMOVE ME

        // Members

        data :: optional <type> _value;

    public:

        // Constructors

        arc();

        // Getters

        const type & value() const;
    };

    // Members

    std :: shared_ptr <arc> _arc;

public:

    // Constructors

    promise();
};

#endif
