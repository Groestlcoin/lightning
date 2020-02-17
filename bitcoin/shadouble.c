#include <bitcoin/shadouble.h>
#include <bitcoin/groestl.h>
#include <ccan/mem/mem.h>
#include <common/type_to_string.h>
#include <common/utils.h>
#include <stdio.h>

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

/*	fprintf(stderr, "groestl512_double_done256 - double hash: ");
	int ii;
	for (ii=0; ii < 64; ii++)
	{
		fprintf(stderr,"%.2x",((uint8_t*)&result2)[ii]);
	};
	fprintf(stderr,"---\ngroestl512_double_done256 - double hash (32)");
	for (ii=0; ii < 32; ii++)
	{
		fprintf(stderr,"%.2x",((uint8_t*)res)[ii]);
	};
	fprintf(stderr,"\n");
*/
}

REGISTER_TYPE_TO_HEXSTR(sha256_double);
//REGISTER_TYPE_TO_HEXSTR(groestl512);

