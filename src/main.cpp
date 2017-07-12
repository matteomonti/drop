#ifdef __main__

#include <iostream>
#include <math.h>

#include "async/async.h"

promise <int> my_int_promise;

promise <int> get_rand()
{
    my_int_promise = promise <int> ();
    return my_int_promise;
}

promise <void> f()
{
    int i;
    int j;

    async
    (
        async_try
        ({
            async_try
            ({
                for(i = 0; i < 1000; i++)
                {
                    await(j) = get_rand();
                    std :: cout << j << std :: endl;

                    if(i == 5)
                        throw 666; // throw "Throwing from within";
                }
            },
            catch(const char * message)
            {
                std :: cout << "Exception: " << message << std :: endl;
            });
        }, catch(...)
        {
            std :: cout << "External, generic catch" << std :: endl;
        });

        async_try
        ({
            throw "Yet another exception";
        },
        catch(const char * message)
        {
            std :: cout << "And from the external catch I still get: " << message << std :: endl;
        });

        std :: cout << "Seppuku now!" << std :: endl;
        throw "Goodbye cruel world";

        return context.resolve();
    );
}

int main()
{
    f().then([]()
    {
        std :: cout << "F completed" << std :: endl;
    }).except([](const std :: exception_ptr & exception)
    {
        std :: cout << "F unexpectedly died with message: ";

        try
        {
            std :: rethrow_exception(exception);
        }
        catch(const char * message)
        {
            std :: cout << message << std :: endl;
        }
        catch(...)
        {
            std :: cout << "(unknown)" << std :: endl;
        }
    });

    for(int i = 0; i < 6; i++)
        my_int_promise.resolve(rand());

    // my_int_promise.reject("Something went wrong");
    // my_int_promise.reject(666);
}

#endif
