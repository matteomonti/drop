// Forward declarations libraries

#include <stdint.h>

// Forward declarations

typedef uint32_t timestamp;
typedef uint64_t microtimestamp;

#if !defined(__forward__) && !defined(__drop__time__time__h)
#define __drop__time__time__h

// libraries

#include <sys/time.h>

// Functions

timestamp time();
microtimestamp microtime();

#endif
