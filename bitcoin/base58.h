#ifndef LIGHTNING_BITCOIN_BASE58_H
#define LIGHTNING_BITCOIN_BASE58_H
#include "config.h"

#include <bitcoin/chainparams.h>
#include <ccan/crypto/ripemd160/ripemd160.h>
#include <ccan/short_types/short_types.h>
#include <ccan/tal/tal.h>
#include <stdbool.h>
#include <stdlib.h>

struct pubkey;
struct privkey;
struct bitcoin_address;

/* Groestlcoin address encoded in base58, with version and checksum */
char *bitcoin_to_base58(const tal_t *ctx, const struct chainparams *chainparams,
			const struct bitcoin_address *addr);
bool bitcoin_from_base58(u8 *version, struct bitcoin_address *addr,
			 const char *base58, size_t len);

/* P2SH address encoded as base58, with version and checksum */
char *p2sh_to_base58(const tal_t *ctx, const struct chainparams *chainparams,
		     const struct ripemd160 *p2sh);
bool p2sh_from_base58(u8 *version, struct ripemd160 *p2sh, const char *base58,
		      size_t len);

bool key_from_base58(const char *base58, size_t base58_len,
		     bool *test_net, struct privkey *priv, struct pubkey *key);

/* Decode a p2pkh or p2sh into the ripemd160 hash */

extern bool (*b58_sha256_impl)(void *, const void *, size_t);

extern bool b58tobin(void *bin, size_t *binsz, const char *b58, size_t b58sz);
extern int b58check(const void *bin, size_t binsz, const char *b58, size_t b58sz);

extern bool b58enc(char *b58, size_t *b58sz, const void *bin, size_t binsz);
extern bool b58check_enc(char *b58c, size_t *b58c_sz, uint8_t ver, const void *data, size_t datasz);


#endif /* LIGHTNING_BITCOIN_BASE58_H */
