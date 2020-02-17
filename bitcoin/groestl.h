#ifndef LIGHTNING_BITCOIN_GROESTL_H
#define LIGHTNING_BITCOIN_GROESTL_H
#include "config.h"
#include "bitcoin/sph_groestl.h"
#include "bitcoin/shadouble.h"
#include <sys/types.h>
#include <common/type_to_string.h>


void groestlhash(void *, const void * , size_t);

/**
 * struct groestl512 - structure representing a completed groestl512.
 * @u.u8: an unsigned char array.
 * @u.u32: a 32-bit integer array.
 *
 * Other fields may be added to the union in future.
 */
struct groestl512 {
	union {
		uint32_t u32[16];
		unsigned char u8[64];
	} u;
};

struct groestl256 {
	union {
		uint32_t u32[8];
		unsigned char u8[32];
	} u;
};

//REGISTER_TYPE_TO_STRING(groestl512, fmt_groestl512);


/**
 * groestl512 - return groestl512 of an object.
 * @groestl512: the groestl512 to fill in
 * @p: pointer to memory,
 * @size: the number of bytes pointed to by @p
 *
 * The bytes pointed to by @p is groestl512 hashed into @groestl512.  This is
 * equivalent to groestl512_init(), groestl512_update() then groestl512_done().
 */
void groestl512(struct groestl512 *sha, const void *p, size_t size);

/**
 * groestl512_init - initialize an groestl512 context.
 * @ctx: the sph_groestl512_context to initialize
 *
 * This must be called before groestl512_update or groestl512_done, or
 * alternately you can assign groestl512_INIT.
 *
 * If it was already initialized, this forgets anything which was
 * hashed before.
 *
 * Example:
 * static void hash_all(const char **arr, struct groestl512 *hash)
 * {
 *	size_t i;
 *	struct sph_groestl512_context ctx;
 *
 *	groestl512_init(&ctx);
 *	for (i = 0; arr[i]; i++)
 *		groestl512_update(&ctx, arr[i], strlen(arr[i]));
 *	groestl512_done(&ctx, hash);
 * }
 */
void groestl512_init(sph_groestl512_context *ctx);

/**
 * groestl512_update - include some memory in the hash.
 * @ctx: the sph_groestl512_context to use
 * @p: pointer to memory,
 * @size: the number of bytes pointed to by @p
 *
 * You can call this multiple times to hash more data, before calling
 * groestl512_done().
 */
void groestl512_update(sph_groestl512_context *ctx, const void *p, size_t size);

/**
 * groestl512_done - finish groestl512 and return the hash
 * @ctx: the sph_groestl512_context to complete
 * @res: the hash to return.
 *
 * Note that @ctx is *destroyed* by this, and must be reinitialized.
 * To avoid that, pass a copy instead.
 */
void groestl512_done(sph_groestl512_context *groestl512, struct groestl512 *res);

/* Add various types to an groestl512 hash */
void groestl512_u8(sph_groestl512_context *ctx, uint8_t v);
void groestl512_u16(sph_groestl512_context *ctx, uint16_t v);
void groestl512_u32(sph_groestl512_context *ctx, uint32_t v);
void groestl512_u64(sph_groestl512_context *ctx, uint64_t v);

/* Add as little-endian */
void groestl512_le16(sph_groestl512_context *ctx, uint16_t v);
void groestl512_le32(sph_groestl512_context *ctx, uint32_t v);
void groestl512_le64(sph_groestl512_context *ctx, uint64_t v);

/* Add as big-endian */
void groestl512_be16(sph_groestl512_context *ctx, uint16_t v);
void groestl512_be32(sph_groestl512_context *ctx, uint32_t v);
void groestl512_be64(sph_groestl512_context *ctx, uint64_t v);

struct groestl512_double256 {
	struct groestl256 groestl;
};

void groestl512_double_done256(sph_groestl512_context *sha256, struct sha256_double *res);


#endif /* LIGHTNING_BITCOIN_GROESTL_H */
