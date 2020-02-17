#include <bitcoin/shadouble.h>
#include <bitcoin/groestl.h>
#include <ccan/mem/mem.h>
#include <common/type_to_string.h>
#include <common/utils.h>

void sha256_double(struct sha256_double *shadouble, const void *p, size_t len)
{
	sha256(&shadouble->sha, memcheck(p, len), len);
	sha256(&shadouble->sha, &shadouble->sha, sizeof(shadouble->sha));
}

void sha256_double_done(struct sha256_ctx *shactx, struct sha256_double *res)
{
	sha256_done(shactx, &res->sha);
	sha256(&res->sha, &res->sha, sizeof(res->sha));
}

void groestl512_double(struct sha256_double *shadouble, const void *p, size_t len)
{
	groestlhash((void *)&shadouble->sha, (void *)p, len);
}

void groestl512_double_done256(sph_groestl512_context *shactx, struct sha256_double *res)
{
	struct groestl512 result;
	groestl512_done(shactx, &result);
	struct groestl512 result2;
	groestl512(&result2, &result, sizeof(result));
	memcpy(res, &result2, 32);
}

REGISTER_TYPE_TO_HEXSTR(sha256_double);

