#include "config.h"
#include <bitcoin/shadouble.h>
#include <bitcoin/groestl.h>
#include <ccan/mem/mem.h>
#include <common/utils.h>
#include <wire/wire.h>

void sha256_double(struct sha256_double *shadouble, const void *p, size_t len)
{
	sha256(&shadouble->sha, memcheck(p, len), len);
	sha256(&shadouble->sha, &shadouble->sha, sizeof(shadouble->sha));
}

void sha256_single(struct sha256_double *shasingle, const void *p, size_t len)
{
	sha256(&shasingle->sha, memcheck(p, len), len);
}

void sha256_double_done(struct sha256_ctx *shactx, struct sha256_double *res)
{
	sha256_done(shactx, &res->sha);
	sha256(&res->sha, &res->sha, sizeof(res->sha));
}

void sha256_single_done(struct sha256_ctx *shactx, struct sha256_double *res)
{
	sha256_done(shactx, &res->sha);
}

char *fmt_sha256_double(const tal_t *ctx, const struct sha256_double *shad)
{
	return tal_hexstr(ctx, shad, sizeof(*shad));
}

void towire_sha256_double(u8 **pptr, const struct sha256_double *sha256d)
{
	towire_sha256(pptr, &sha256d->sha);
}

void fromwire_sha256_double(const u8 **cursor, size_t *max,
			    struct sha256_double *sha256d)
{
	fromwire_sha256(cursor, max, &sha256d->sha);
}
