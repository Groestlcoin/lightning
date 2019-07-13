/* Converted to C by Rusty Russell, based on bitcoin source: */
// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
/*
 * Copyright 2012-2014 Luke Dashjr
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the standard MIT license.  See COPYING for more details.
 */

#include "address.h"
#include "base58.h"
#include "privkey.h"
#include "pubkey.h"
#include "shadouble.h"
#include <arpa/inet.h>
#include <assert.h>
#include <bitcoin/base58.h>
#include <bitcoin/chainparams.h>
#include <bitcoin/groestl.h>
#include <ccan/build_assert/build_assert.h>
#include <ccan/tal/str/str.h>
#include <common/utils.h>
#include <string.h>
#include <wally_core.h>
bool (*b58_sha256_impl)(void *, const void *, size_t) = NULL;

static const int8_t b58digits_map[] = {
	-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
	-1, 0, 1, 2, 3, 4, 5, 6,  7, 8,-1,-1,-1,-1,-1,-1,
	-1, 9,10,11,12,13,14,15, 16,-1,17,18,19,20,21,-1,
	22,23,24,25,26,27,28,29, 30,31,32,-1,-1,-1,-1,-1,
	-1,33,34,35,36,37,38,39, 40,41,42,43,-1,44,45,46,
	47,48,49,50,51,52,53,54, 55,56,57,-1,-1,-1,-1,-1,
};

bool b58tobin(void *bin, size_t *binszp, const char *b58, size_t b58sz)
{
	size_t binsz = *binszp;
	const unsigned char *b58u = (void*)b58;
	unsigned char *binu = bin;
	size_t outisz = (binsz + 3) / 4;
	uint32_t outi[outisz];
	uint64_t t;
	uint32_t c;
	size_t i, j;
	uint8_t bytesleft = binsz % 4;
	uint32_t zeromask = bytesleft ? (0xffffffff << (bytesleft * 8)) : 0;
	unsigned zerocount = 0;

	if (!b58sz)
		b58sz = strlen(b58);

	memset(outi, 0, outisz * sizeof(*outi));

	// Leading zeros, just count
	for (i = 0; i < b58sz && b58u[i] == '1'; ++i)
		++zerocount;

	for ( ; i < b58sz; ++i)
	{
		if (b58u[i] & 0x80)
			// High-bit set on invalid digit
			return false;
		if (b58digits_map[b58u[i]] == -1)
			// Invalid base58 digit
			return false;
		c = (unsigned)b58digits_map[b58u[i]];
		for (j = outisz; j--; )
		{
			t = ((uint64_t)outi[j]) * 58 + c;
			c = (t & 0x3f00000000) >> 32;
			outi[j] = t & 0xffffffff;
		}
		if (c)
			// Output number too big (carry to the next int32)
			return false;
		if (outi[0] & zeromask)
			// Output number too big (last int32 filled too far)
			return false;
	}

	j = 0;
	switch (bytesleft) {
		case 3:
			*(binu++) = (outi[0] &   0xff0000) >> 16;
		case 2:
			*(binu++) = (outi[0] &     0xff00) >>  8;
		case 1:
			*(binu++) = (outi[0] &       0xff);
			++j;
		default:
			break;
	}

	for (; j < outisz; ++j)
	{
		*(binu++) = (outi[j] >> 0x18) & 0xff;
		*(binu++) = (outi[j] >> 0x10) & 0xff;
		*(binu++) = (outi[j] >>    8) & 0xff;
		*(binu++) = (outi[j] >>    0) & 0xff;
	}

	// Count canonical base58 byte count
	binu = bin;
	for (i = 0; i < binsz; ++i)
	{
		if (binu[i])
			break;
		--*binszp;
	}
	*binszp += zerocount;

	return true;
}

static
bool my_dblsha256(void *hash, const void *data, size_t datasz)
{
		return b58_sha256_impl(hash, data, datasz);
}

int b58check(const void *bin, size_t binsz, const char *base58str, size_t b58sz)
{
	unsigned char buf[32];
	const uint8_t *binc = bin;
	unsigned i;
	if (binsz < 4)
		return -4;
	if (!my_dblsha256(buf, bin, binsz - 4))
		return -2;
	if (memcmp(&binc[binsz - 4], buf, 4))
		return -1;

	// Check number of zeros is correct AFTER verifying checksum (to avoid possibility of accessing base58str beyond the end)
	for (i = 0; binc[i] == '\0' && base58str[i] == '1'; ++i)
	{}  // Just finding the end of zeros, nothing to do in loop
	if (binc[i] == '\0' || base58str[i] == '1')
		return -3;

	return binc[0];
}

static const char b58digits_ordered[] = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";

bool b58enc(char *b58, size_t *b58sz, const void *data, size_t binsz)
{
	const uint8_t *bin = data;
	int carry;
	ssize_t i, j, high, zcount = 0;
	size_t size;

	while (zcount < binsz && !bin[zcount])
		++zcount;

	size = (binsz - zcount) * 138 / 100 + 1;
	uint8_t buf[size];
	memset(buf, 0, size);

	for (i = zcount, high = size - 1; i < binsz; ++i, high = j)
	{
		for (carry = bin[i], j = size - 1; (j > high) || carry; --j)
		{
			carry += 256 * buf[j];
			buf[j] = carry % 58;
			carry /= 58;
		}
	}

	for (j = 0; j < size && !buf[j]; ++j);

	if (*b58sz <= zcount + size - j)
	{
		*b58sz = zcount + size - j + 1;
		return false;
	}

	if (zcount)
		memset(b58, '1', zcount);
	for (i = zcount; j < size; ++i, ++j)
		b58[i] = b58digits_ordered[buf[j]];
	b58[i] = '\0';
	*b58sz = i + 1;

	return true;
}

bool b58check_enc(char *b58c, size_t *b58c_sz, uint8_t ver, const void *data, size_t datasz)
{
	uint8_t buf[1 + datasz + 0x20];
	uint8_t *hash = &buf[1 + datasz];

	buf[0] = ver;
	memcpy(&buf[1], data, datasz);
	if (!my_dblsha256(hash, buf, datasz + 1))
	{
		*b58c_sz = 0;
		return false;
	}

	return b58enc(b58c, b58c_sz, buf, 1 + datasz + 4);
}


	groestlhash((void *)digest, (void *)data, datasz);

static char *to_base58(const tal_t *ctx, u8 version,
			   const struct ripemd160 *rmd)
{
	char *out;
	size_t total_length = sizeof(*rmd) + 1;
	u8 buf[total_length];
	buf[0] = version;
	memcpy(buf + 1, rmd, sizeof(*rmd));

	if (wally_base58_from_bytes((const unsigned char *) buf, total_length, BASE58_FLAG_CHECKSUM, &out) != WALLY_OK) {
		return NULL;
	}else{
		char *res = tal_strdup(ctx, out);
		wally_free_string(out);
		return res;
	}
}

char *bitcoin_to_base58(const tal_t *ctx, const struct chainparams *chainparams,
			const struct bitcoin_address *addr)
{
	return to_base58(ctx, chainparams->p2pkh_version, &addr->addr);
}

char *p2sh_to_base58(const tal_t *ctx, const struct chainparams *chainparams,
			 const struct ripemd160 *p2sh)
{
	return to_base58(ctx, chainparams->p2sh_version, p2sh);
}

static bool from_base58(u8 *version,
			struct ripemd160 *rmd,
			const char *base58, size_t base58_len)
{
	u8 buf[1 + sizeof(*rmd) + 4];
	/* Avoid memcheck complaining if decoding resulted in a short value */
	size_t buflen = sizeof(buf);
	memset(buf, 0, buflen);
	char *terminated_base58 = tal_dup_arr(NULL, char, base58, base58_len, 1);
	terminated_base58[base58_len] = '\0';

	size_t written = 0;
	int r = wally_base58_to_bytes(terminated_base58, BASE58_FLAG_CHECKSUM, buf, buflen, &written);
	tal_free(terminated_base58);
	if (r != WALLY_OK || written > buflen) {
		return false;
	}
	*version = buf[0];
	memcpy(rmd, buf + 1, sizeof(*rmd));
	return true;
}

bool bitcoin_from_base58(u8 *version, struct bitcoin_address *addr,
			 const char *base58, size_t len)
{
	return from_base58(version, &addr->addr, base58, len);
}


			  struct ripemd160 *p2sh,
			  const char *base58, size_t len)
{

	return from_base58(version, p2sh, base58, len);
}

bool ripemd160_from_base58(u8 *version, struct ripemd160 *rmd,
			   const char *base58, size_t base58_len)
{
	return from_base58(version, rmd, base58, base58_len);
}

bool key_from_base58(const char *base58, size_t base58_len,
			 bool *test_net, struct privkey *priv, struct pubkey *key)
{
	// 1 byte version, 32 byte private key, 1 byte compressed, 4 byte checksum
	u8 keybuf[1 + 32 + 1 + 4];
	char *terminated_base58 = tal_dup_arr(NULL, char, base58, base58_len, 1);
	terminated_base58[base58_len] = '\0';
	size_t keybuflen = sizeof(keybuf);


	size_t written = 0;
	int r = wally_base58_to_bytes(terminated_base58, BASE58_FLAG_CHECKSUM, keybuf, keybuflen, &written);
	wally_bzero(terminated_base58, base58_len + 1);
	tal_free(terminated_base58);
	if (r != WALLY_OK || written > keybuflen)
		return false;

	/* Byte after key should be 1 to represent a compressed key. */
	if (keybuf[1 + 32] != 1)
		return false;

	if (keybuf[0] == 128)
		*test_net = false;
	else if (keybuf[0] == 239)
		*test_net = true;
	else
		return false;

	/* Copy out secret. */
	memcpy(priv->secret.data, keybuf + 1, sizeof(priv->secret.data));

	if (!secp256k1_ec_seckey_verify(secp256k1_ctx, priv->secret.data))
		return false;

	/* Get public key, too. */
	if (!pubkey_from_privkey(priv, key))
		return false;

	return true;
}
