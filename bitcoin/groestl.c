#include <bitcoin/groestl.h>
#include <bitcoin/sph_groestl.h>
#include <bitcoin/sph_types.h>
#include <ccan/build_assert/build_assert.h>
#include <ccan/tal/str/str.h>
#include <ccan/endian/endian.h>
#include <common/utils.h>
#include <stdio.h>

void groestlhash(void *output, const void *input , size_t len)
{
	uint32_t hash[16];
	sph_groestl512_context ctx_1,ctx_2;

	/*int ii;
	printf("result input: ");
	for (ii=0; ii < len; ii++)
	{
		printf ("%.2x",((uint8_t*)input)[ii]);
	};
	printf ("\n");
	*/
	sph_groestl512_init(&ctx_1);
	sph_groestl512(&ctx_1, input, len);
	sph_groestl512_close(&ctx_1, hash);

	sph_groestl512_init(&ctx_2);
	sph_groestl512(&ctx_2, hash, 64);
	sph_groestl512_close(&ctx_2, hash);

	memcpy(output, hash, 32);

	/*
	printf("result output: ");
	for (ii=0; ii < 32; ii++)
	{
	printf ("%.2x",((uint8_t*)output)[ii]);
	};
	printf ("---\n");
	for (ii=0; ii < 32; ii++)
	{
		printf ("%.2x",((uint8_t*)hash)[ii]);
	};
	printf ("\n");
	*/
}

static void check_groestl512(sph_groestl512_context *ctx UNUSED)
{
//	assert(ctx->bytes != (size_t)-1);
}

void groestl512_init(sph_groestl512_context *ctx)
{
	sph_groestl512_init(ctx);
}

void groestl512_update(sph_groestl512_context *ctx, const void *p, size_t size)
{
	check_groestl512(ctx);
	sph_groestl512(ctx, p, size);
}

void groestl512_done(sph_groestl512_context *ctx, struct groestl512 * res)
{
	sph_groestl512_close(ctx, res->u.u8);
}

void groestl512(struct groestl512 *sha, const void *p, size_t size)
{
	sph_groestl512_context ctx;

	groestl512_init(&ctx);
	groestl512_update(&ctx, p, size);
	groestl512_done(&ctx, sha);
}

void groestl512_u8(sph_groestl512_context *ctx, uint8_t v)
{
	groestl512_update(ctx, &v, sizeof(v));
}

void groestl512_u16(sph_groestl512_context *ctx, uint16_t v)
{
	groestl512_update(ctx, &v, sizeof(v));
}

void groestl512_u32(sph_groestl512_context *ctx, uint32_t v)
{
	groestl512_update(ctx, &v, sizeof(v));
}

void groestl512_u64(sph_groestl512_context *ctx, uint64_t v)
{
	groestl512_update(ctx, &v, sizeof(v));
}

/* Add as little-endian */
void groestl512_le16(sph_groestl512_context *ctx, uint16_t v)
{
	leint16_t lev = cpu_to_le16(v);
	groestl512_update(ctx, &lev, sizeof(lev));
}

void groestl512_le32(sph_groestl512_context *ctx, uint32_t v)
{
	leint32_t lev = cpu_to_le32(v);
	groestl512_update(ctx, &lev, sizeof(lev));
}

void groestl512_le64(sph_groestl512_context *ctx, uint64_t v)
{
	leint64_t lev = cpu_to_le64(v);
	groestl512_update(ctx, &lev, sizeof(lev));
}

/* Add as big-endian */
void groestl512_be16(sph_groestl512_context *ctx, uint16_t v)
{
	beint16_t bev = cpu_to_be16(v);
	groestl512_update(ctx, &bev, sizeof(bev));
}

void groestl512_be32(sph_groestl512_context *ctx, uint32_t v)
{
	beint32_t bev = cpu_to_be32(v);
	groestl512_update(ctx, &bev, sizeof(bev));
}

void groestl512_be64(sph_groestl512_context *ctx, uint64_t v)
{
	beint64_t bev = cpu_to_be64(v);
	groestl512_update(ctx, &bev, sizeof(bev));
}
