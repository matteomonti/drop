// Includes

#include "time.h"

// Functions

timestamp time()
{
    return (timestamp) (microtime() / 1000000);
}

microtimestamp microtime()
{
    struct timeval timestamp;
    gettimeofday(&timestamp, nullptr);
    return timestamp.tv_sec * 1000000 + timestamp.tv_usec;
}
