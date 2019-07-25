#include <bitcoin/shadouble.h>
#include <bitcoin/groestl.h>
#include <ccan/mem/mem.h>
#include <common/type_to_string.h>
#include <common/utils.h>

void groestl512_double(struct sha256_double *shadouble, const void *p, size_t len)
{
	groestlhash((void *)&shadouble->sha, (void *)p, len);
}

void sha256_double(struct sha256_double *shadouble, const void *p, size_t len)
{
	sha256(&shadouble->sha, memcheck(p, len), len);
	sha256(&shadouble->sha, &shadouble->sha, sizeof(shadouble->sha));
}

REGISTER_TYPE_TO_HEXSTR(sha256_double);
