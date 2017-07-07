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

    template <typename> struct traits;
    class callback_base;
    template <typename, bool> class callback;
    template <typename, bool> class arc_base;
    class arc;

    // Service nested classes

    template <typename lambda> struct traits
    {
        template <typename> struct is_promise;

        template <typename> struct is_promise
        {
            static constexpr bool value = false;
        };

        template <typename ptype> struct is_promise <promise <ptype>>
        {
            static constexpr bool value = true;
        };

        template <typename, bool> struct pswitch;

        template <bool dummy> struct pswitch <void, dummy>
        {
            static constexpr bool valid = utils :: is_callable <lambda> :: value;
            typedef std :: result_of_t <lambda()> return_type;
            static constexpr bool chainable = is_promise <return_type> :: value;
            typedef std :: conditional_t <chainable, return_type, void> then_type;
        };

        template <typename ptype, bool dummy> struct pswitch
        {
            static constexpr bool valid = utils :: is_callable <lambda, const ptype &> :: value;
            typedef std :: result_of_t <lambda(const ptype &)> return_type;
            static constexpr bool chainable = is_promise <return_type> :: value;
            typedef std :: conditional_t <chainable, return_type, void> then_type;
        };

        static constexpr bool valid = pswitch <type, false> :: valid;
        typedef typename pswitch <type, false> :: return_type return_type;
        static constexpr bool chainable = pswitch <type, false> :: chainable;
        typedef typename pswitch <type, false> :: then_type then_type;
    };

    class callback_base
    {
    public:

        // Destructor

        virtual ~callback_base();

        // Interface methods

        virtual void run(const arc &) = 0;
    };

    template <typename lambda, bool = traits <lambda> :: chainable> class callback;

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

        void run(const arc &);
    };

    template <typename lambda> class callback <lambda, true> : public callback_base
    {
        // Typedefs

        typedef typename traits <lambda> :: return_type chain;

        // Members

        lambda _callback;
        chain _promise;

    public:

        // Constructors

        callback(const lambda &);

        // Getters

        chain promise() const;

        // Methods

        void run(const arc &);
    };

    template <bool dummy> class arc_base <void, dummy>
    {
    protected:

        // Members

        bool _resolved;

    public:

        // Constructors

        arc_base();

        // Getters

        const bool & resolved() const;

        // Methods

        template <typename lambda> auto call(const lambda &) const;

    protected:

        // Private methods

        void resolve();
    };

    template <typename ptype, bool dummy> class arc_base
    {
    protected:

        // Members

        data :: optional <type> _value;

    public:

        // Constructors

        arc_base();

        // Getters

        const bool & resolved() const;

        // Methods

        template <typename lambda> auto call(const lambda &) const;

    protected:

        // Private methods

        void resolve(const ptype &);
    };

    class arc : public arc_base <type, false>
    {
        // Members

        std :: shared_ptr <arc> _alias;
        callback_base * _callbacks[settings :: callbacks];
        size_t _size;

    public:

        // Constructors

        arc();

        // Methods

        template <typename lambda> typename traits <lambda> :: then_type then(const lambda &);
        template <typename... atypes, std :: enable_if_t <(std :: is_same <type, void> :: value && sizeof...(atypes) == 0) || (!(std :: is_same <type, void> :: value) && sizeof...(atypes) == 1)> * = nullptr> void resolve(const atypes &...);
        void alias(const promise &);
    };

    // Members

    std :: shared_ptr <arc> _arc;

public:

    // Constructors

    promise();

    // Methods

    template <typename lambda, typename std :: enable_if_t <traits <lambda> :: valid> * = nullptr> auto then(const lambda &);
    template <typename... atypes, std :: enable_if_t <(std :: is_same <type, void> :: value && sizeof...(atypes) == 0) || (!(std :: is_same <type, void> :: value) && sizeof...(atypes) == 1)> * = nullptr> void resolve(const atypes &...);

private:

    // Private methods

    void alias(const promise &);
};

#endif
