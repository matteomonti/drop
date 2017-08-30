#ifndef __lib__pmurmurhash32__pmurmurhash32__h
#define __lib__pmurmurhash32__pmurmurhash32__h

/*-----------------------------------------------------------------------------
 * MurmurHash3 was written by Austin Appleby, and is placed in the public
 * domain.
 *
 * This implementation was written by Shane Day, and is also public domain.
 *
 * This is a portable ANSI C implementation of MurmurHash3_x86_32 (Murmur3A)
 * with support for progressive processing.
 */

/* ------------------------------------------------------------------------- */

#include <iostream>

/* ------------------------------------------------------------------------- */
/* Prototypes */

void PMurHash32_Process(uint32_t *ph1, uint32_t *pcarry, const void *key, size_t len);
uint32_t PMurHash32_Result(uint32_t h1, uint32_t carry, uint32_t total_length);
uint32_t PMurHash32(uint32_t seed, const void *key, int len);

void PMurHash32_test(const void *key, int len, uint32_t seed, void *out);

#endif
