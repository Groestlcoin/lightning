#include "chainparams.h"
#include <ccan/array_size/array_size.h>
#include <ccan/str/str.h>
#include <string.h>

/* Version codes for BIP32 extended keys in libwally-core.
 * Stolen from wally_bip32.h in libwally-core*/
#define BIP32_VER_MAIN_PUBLIC  0x0488B21E
#define BIP32_VER_MAIN_PRIVATE 0x0488ADE4
#define BIP32_VER_TEST_PUBLIC  0x043587CF
#define BIP32_VER_TEST_PRIVATE 0x04358394

const struct chainparams networks[] = {
    {.network_name = "groestlcoin",
     .bip173_name = "grs",
     .genesis_blockhash = {{{.u.u8 = {0x23, 0x90, 0x63, 0x3b, 0x70, 0xf0, 0x62, 0xcb, 0x3a, 0x3d, 0x68, 0x14, 0xb6, 0x7e, 0x29, 0xa8, 0x0d, 0x9d, 0x75, 0x81, 0xdb, 0x0b, 0xcc, 0x49, 0x4d, 0x59, 0x7c, 0x92, 0xc5, 0x0a, 0x00, 0x00}}}},
     .rpc_port = 1441,
     .cli = "groestlcoin-cli",
     .cli_args = NULL,
     .dust_limit = { 546 },
     /* BOLT #2:
      *
      * The sending node:
      *...
      *   - MUST set `funding_satoshis` to less than 2^24 satoshi.
      */
     .max_funding = AMOUNT_SAT_INIT((1 << 24) - 1),
     .max_payment = AMOUNT_MSAT_INIT(0xFFFFFFFFULL),
     /* "Lightning Charge Powers Developers & Blockstream Store" */
     .when_lightning_became_cool = 504500,
     .p2pkh_version = 36,
     .p2sh_version = 5,
     .testnet = false,
     .bip32_key_version = {.bip32_pubkey_version = BIP32_VER_MAIN_PUBLIC, .bip32_privkey_version = BIP32_VER_MAIN_PRIVATE}},
    {.network_name = "regtest",
     .bip173_name = "grsrt",
     .genesis_blockhash = {{{.u.u8 = {0x36, 0xcd, 0xf2, 0xdc, 0xb7, 0x55, 0x62, 0x87, 0x28, 0x2a, 0x05, 0xc0, 0x64, 0x01, 0x23, 0x23, 0xba, 0xe6, 0x63, 0xc1, 0x6e, 0xd3, 0xcd, 0x98, 0x98, 0xfc, 0x50, 0xbb, 0xff, 0x00, 0x00, 0x00}}}},
     .rpc_port = 18443,
     .cli = "groestlcoin-cli",
     .cli_args = "-regtest",
     .dust_limit = { 546 },
     .max_funding = AMOUNT_SAT_INIT((1 << 24) - 1),
     .max_payment = AMOUNT_MSAT_INIT(0xFFFFFFFFULL),
     .when_lightning_became_cool = 1,
     .p2pkh_version = 111,
     .p2sh_version = 196,
     .testnet = true,
     .bip32_key_version = {.bip32_pubkey_version = BIP32_VER_TEST_PUBLIC, .bip32_privkey_version = BIP32_VER_TEST_PRIVATE}},
    {.network_name = "testnet",
     .bip173_name = "tgrs",
     .genesis_blockhash = {{{.u.u8 = {0x36, 0xcd, 0xf2, 0xdc, 0xb7, 0x55, 0x62, 0x87, 0x28, 0x2a, 0x05, 0xc0, 0x64, 0x01, 0x23, 0x23, 0xba, 0xe6, 0x63, 0xc1, 0x6e, 0xd3, 0xcd, 0x98, 0x98, 0xfc, 0x50, 0xbb, 0xff, 0x00, 0x00, 0x00}}}},
     .rpc_port = 17766,
     .cli = "groestlcoin-cli",
     .cli_args = "-testnet",
     .dust_limit = { 546 },
     .max_funding = AMOUNT_SAT_INIT((1 << 24) - 1),
     .max_payment = AMOUNT_MSAT_INIT(0xFFFFFFFFULL),
     .when_lightning_became_cool = 1,
     .p2pkh_version = 111,
     .p2sh_version = 196,
     .testnet = true,
     .bip32_key_version = {.bip32_pubkey_version = BIP32_VER_TEST_PUBLIC, .bip32_privkey_version = BIP32_VER_TEST_PRIVATE}}
};

const struct chainparams *chainparams_for_network(const char *network_name)
{
	for (size_t i = 0; i < ARRAY_SIZE(networks); i++) {
		if (streq(network_name, networks[i].network_name)) {
			return &networks[i];
		}
	}
	return NULL;
}

const struct chainparams *chainparams_by_chainhash(const struct bitcoin_blkid *chain_hash)
{
	for (size_t i = 0; i < ARRAY_SIZE(networks); i++) {
		if (bitcoin_blkid_eq(chain_hash, &networks[i].genesis_blockhash)) {
			return &networks[i];
		}
	}
	return NULL;
}

const struct chainparams *chainparams_by_bip173(const char *bip173_name)
{
	for (size_t i = 0; i < ARRAY_SIZE(networks); i++) {
		if (streq(bip173_name, networks[i].bip173_name)) {
			return &networks[i];
		}
	}
	return NULL;
}
