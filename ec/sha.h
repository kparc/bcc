/* SHA512
 * Daniel Beer <dlbeer@gmail.com>, 22 Apr 2014
 *
 * This file is in the public domain.
 */

#ifndef SHA512_H_
#define SHA512_H_

#if !defined(COMPACT_DISABLE_ED25519) || !defined(COMPACT_DISABLE_X25519_DERIVE)
#include <stdint.h>
#include <stddef.h>
#include <string.h>

#define dsn memcpy
#define mset memset
#define mmv memmove

/* SHA512 state. State is updated as data is fed in, and then the final
 * hash can be read out in slices.
 *
 * Data is fed in as a sequence of full blocks terminated by a single
 * partial block.
 */
struct sha_state {
	uint64_t  h[8];
};

/* Initial state */
extern const struct sha_state sha_initial_state;

/* Set up a new context */
static inline void sha_ini(struct sha_state *s)
{
	dsn(s, &sha_initial_state, sizeof(*s));
}

/* Feed a full block in */
#define SHA512_BLOCK_SIZE  128

void sha_add(struct sha_state *s, const uint8_t *blk);

/* Feed the last partial block in. The total stream size must be
 * specified. The size of the block given is assumed to be (total_size %
 * SHA512_BLOCK_SIZE). This might be zero, but you still need to call
 * this function to terminate the stream.
 */
void sha_end(struct sha_state *s, const uint8_t *blk,
		  size_t total_size);

/* Fetch a slice of the hash result. */
#define SHA512_HASH_SIZE  64

void sha_get(const struct sha_state *s, uint8_t *hash,
		unsigned int offset, unsigned int len);

#endif
#endif

//:~
