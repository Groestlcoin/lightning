#include "config.h"
#include "../bigsize.c"
#include "../blindedpath.c"
#include "../blinding.c"
#include "../hmac.c"
#include "../type_to_string.c"
#include <ccan/tal/grab_file/grab_file.h>
#include <ccan/tal/path/path.h>
#include <common/channel_id.h>
#include <common/json.h>
#include <common/json_helpers.h>
#include <common/json_stream.h>
#include <common/setup.h>
#include <common/wireaddr.h>
#include <stdio.h>

/* AUTOGENERATED MOCKS START */
/* Generated stub for amount_asset_is_main */
bool amount_asset_is_main(struct amount_asset *asset UNNEEDED)
{ fprintf(stderr, "amount_asset_is_main called!\n"); abort(); }
/* Generated stub for amount_asset_to_sat */
struct amount_sat amount_asset_to_sat(struct amount_asset *asset UNNEEDED)
{ fprintf(stderr, "amount_asset_to_sat called!\n"); abort(); }
/* Generated stub for amount_msat */
struct amount_msat amount_msat(u64 millisatoshis UNNEEDED)
{ fprintf(stderr, "amount_msat called!\n"); abort(); }
/* Generated stub for amount_sat */
struct amount_sat amount_sat(u64 satoshis UNNEEDED)
{ fprintf(stderr, "amount_sat called!\n"); abort(); }
/* Generated stub for amount_sat_add */
 bool amount_sat_add(struct amount_sat *val UNNEEDED,
				       struct amount_sat a UNNEEDED,
				       struct amount_sat b UNNEEDED)
{ fprintf(stderr, "amount_sat_add called!\n"); abort(); }
/* Generated stub for amount_sat_eq */
bool amount_sat_eq(struct amount_sat a UNNEEDED, struct amount_sat b UNNEEDED)
{ fprintf(stderr, "amount_sat_eq called!\n"); abort(); }
/* Generated stub for amount_sat_greater_eq */
bool amount_sat_greater_eq(struct amount_sat a UNNEEDED, struct amount_sat b UNNEEDED)
{ fprintf(stderr, "amount_sat_greater_eq called!\n"); abort(); }
/* Generated stub for amount_sat_sub */
 bool amount_sat_sub(struct amount_sat *val UNNEEDED,
				       struct amount_sat a UNNEEDED,
				       struct amount_sat b UNNEEDED)
{ fprintf(stderr, "amount_sat_sub called!\n"); abort(); }
/* Generated stub for amount_sat_to_asset */
struct amount_asset amount_sat_to_asset(struct amount_sat *sat UNNEEDED, const u8 *asset UNNEEDED)
{ fprintf(stderr, "amount_sat_to_asset called!\n"); abort(); }
/* Generated stub for amount_sat_to_msat */
 bool amount_sat_to_msat(struct amount_msat *msat UNNEEDED,
					   struct amount_sat sat UNNEEDED)
{ fprintf(stderr, "amount_sat_to_msat called!\n"); abort(); }
/* Generated stub for amount_tx_fee */
struct amount_sat amount_tx_fee(u32 fee_per_kw UNNEEDED, size_t weight UNNEEDED)
{ fprintf(stderr, "amount_tx_fee called!\n"); abort(); }
/* Generated stub for fmt_wireaddr_without_port */
char *fmt_wireaddr_without_port(const tal_t *ctx UNNEEDED, const struct wireaddr *a UNNEEDED)
{ fprintf(stderr, "fmt_wireaddr_without_port called!\n"); abort(); }
/* Generated stub for fromwire_amount_msat */
struct amount_msat fromwire_amount_msat(const u8 **cursor UNNEEDED, size_t *max UNNEEDED)
{ fprintf(stderr, "fromwire_amount_msat called!\n"); abort(); }
/* Generated stub for fromwire_amount_sat */
struct amount_sat fromwire_amount_sat(const u8 **cursor UNNEEDED, size_t *max UNNEEDED)
{ fprintf(stderr, "fromwire_amount_sat called!\n"); abort(); }
/* Generated stub for fromwire_channel_id */
bool fromwire_channel_id(const u8 **cursor UNNEEDED, size_t *max UNNEEDED,
			 struct channel_id *channel_id UNNEEDED)
{ fprintf(stderr, "fromwire_channel_id called!\n"); abort(); }
/* Generated stub for fromwire_node_id */
void fromwire_node_id(const u8 **cursor UNNEEDED, size_t *max UNNEEDED, struct node_id *id UNNEEDED)
{ fprintf(stderr, "fromwire_node_id called!\n"); abort(); }
/* Generated stub for fromwire_wireaddr */
bool fromwire_wireaddr(const u8 **cursor UNNEEDED, size_t *max UNNEEDED, struct wireaddr *addr UNNEEDED)
{ fprintf(stderr, "fromwire_wireaddr called!\n"); abort(); }
/* Generated stub for json_add_member */
void json_add_member(struct json_stream *js UNNEEDED,
		     const char *fieldname UNNEEDED,
		     bool quote UNNEEDED,
		     const char *fmt UNNEEDED, ...)
{ fprintf(stderr, "json_add_member called!\n"); abort(); }
/* Generated stub for json_member_direct */
char *json_member_direct(struct json_stream *js UNNEEDED,
			 const char *fieldname UNNEEDED, size_t extra UNNEEDED)
{ fprintf(stderr, "json_member_direct called!\n"); abort(); }
/* Generated stub for json_object_end */
void json_object_end(struct json_stream *js UNNEEDED)
{ fprintf(stderr, "json_object_end called!\n"); abort(); }
/* Generated stub for json_object_start */
void json_object_start(struct json_stream *ks UNNEEDED, const char *fieldname UNNEEDED)
{ fprintf(stderr, "json_object_start called!\n"); abort(); }
/* Generated stub for node_id_from_hexstr */
bool node_id_from_hexstr(const char *str UNNEEDED, size_t slen UNNEEDED, struct node_id *id UNNEEDED)
{ fprintf(stderr, "node_id_from_hexstr called!\n"); abort(); }
/* Generated stub for parse_amount_msat */
bool parse_amount_msat(struct amount_msat *msat UNNEEDED, const char *s UNNEEDED, size_t slen UNNEEDED)
{ fprintf(stderr, "parse_amount_msat called!\n"); abort(); }
/* Generated stub for parse_amount_sat */
bool parse_amount_sat(struct amount_sat *sat UNNEEDED, const char *s UNNEEDED, size_t slen UNNEEDED)
{ fprintf(stderr, "parse_amount_sat called!\n"); abort(); }
/* Generated stub for towire_amount_msat */
void towire_amount_msat(u8 **pptr UNNEEDED, const struct amount_msat msat UNNEEDED)
{ fprintf(stderr, "towire_amount_msat called!\n"); abort(); }
/* Generated stub for towire_amount_sat */
void towire_amount_sat(u8 **pptr UNNEEDED, const struct amount_sat sat UNNEEDED)
{ fprintf(stderr, "towire_amount_sat called!\n"); abort(); }
/* Generated stub for towire_channel_id */
void towire_channel_id(u8 **pptr UNNEEDED, const struct channel_id *channel_id UNNEEDED)
{ fprintf(stderr, "towire_channel_id called!\n"); abort(); }
/* Generated stub for towire_node_id */
void towire_node_id(u8 **pptr UNNEEDED, const struct node_id *id UNNEEDED)
{ fprintf(stderr, "towire_node_id called!\n"); abort(); }
/* Generated stub for towire_wireaddr */
void towire_wireaddr(u8 **pptr UNNEEDED, const struct wireaddr *addr UNNEEDED)
{ fprintf(stderr, "towire_wireaddr called!\n"); abort(); }
/* AUTOGENERATED MOCKS END */

static u8 *json_to_enctlvs(const tal_t *ctx,
			   const char *buf, const jsmntok_t *tlvs)
{
	struct tlv_encrypted_data_tlv *enctlv = tlv_encrypted_data_tlv_new(tmpctx);
	size_t i;
	const jsmntok_t *t;
	u8 *ret, *appended = tal_arr(tmpctx, u8, 0);

	json_for_each_obj(i, t, tlvs) {
		if (json_tok_streq(buf, t, "short_channel_id")) {
			enctlv->short_channel_id = tal(enctlv, struct short_channel_id);
			assert(json_to_short_channel_id(buf, t+1,
							enctlv->short_channel_id));
		} else if (json_tok_streq(buf, t, "padding")) {
			enctlv->padding = json_tok_bin_from_hex(enctlv,
								buf, t+1);
			assert(enctlv->padding);
		} else if (json_tok_streq(buf, t, "next_node_id")) {
			enctlv->next_node_id = tal(enctlv, struct pubkey);
			assert(json_to_pubkey(buf, t+1,
					      enctlv->next_node_id));
		} else if (json_tok_streq(buf, t, "path_id")) {
			enctlv->path_id = json_tok_bin_from_hex(enctlv,
								buf, t+1);
			assert(enctlv->path_id);
		} else {
			u16 tagnum;
			u8 *val;
			assert(json_tok_startswith(buf, t, "unknown_tag_"));
			tagnum = atoi(buf + t->start + strlen("unknown_tag_"));
			assert(tagnum);
			val = json_tok_bin_from_hex(enctlv, buf, t+1);
			assert(val);

			/* We can't actually represent these in a way towire_
			 * will see, so we literally append them */
			towire_bigsize(&appended, tagnum);
			towire_bigsize(&appended, tal_bytelen(val));
			towire_u8_array(&appended, val, tal_bytelen(val));
		}
	}
	ret = tal_arr(ctx, u8, 0);
	towire_encrypted_data_tlv(&ret, enctlv);
	towire_u8_array(&ret, appended, tal_bytelen(appended));
	return ret;
}

int main(int argc, char *argv[])
{
	char *json;
	size_t i;
	jsmn_parser parser;
	jsmntok_t toks[5000];
	const jsmntok_t *t, *hops_tok;
	struct pubkey *ids;
	u8 **enctlvs;
	struct privkey blinding;

	common_setup(argv[0]);

	if (argv[1])
		json = grab_file(tmpctx, argv[1]);
	else {
		char *dir = getenv("BOLTDIR");
		json = grab_file(tmpctx,
				 path_join(tmpctx,
					   dir ? dir : "../lightning-rfc",
					   "bolt04/route-blinding-test.json"));
		if (!json) {
			printf("test file not found, skipping\n");
			goto out;
		}
	}

	jsmn_init(&parser);
	if (jsmn_parse(&parser, json, strlen(json), toks, ARRAY_SIZE(toks)) < 0)
		abort();

	hops_tok = json_get_member(json, json_get_member(json, toks, "route"), "hops");
	ids = tal_arr(tmpctx, struct pubkey, hops_tok->size);
	enctlvs = tal_arr(tmpctx, u8 *, hops_tok->size);

	json_for_each_arr(i, t, hops_tok) {
		u8 *expected;
		assert(json_to_pubkey(json, json_get_member(json, t, "node_id"),
				      &ids[i]));
		enctlvs[i] = json_tok_bin_from_hex(enctlvs, json,
						   json_get_member(json, t, "encoded_tlvs"));
		expected = json_to_enctlvs(tmpctx, json,
					   json_get_member(json, t, "tlvs"));
		assert(memeq(expected, tal_bytelen(expected),
			     enctlvs[i], tal_bytelen(enctlvs[i])));
	}

	/* Now do the blinding. */
	hops_tok = json_get_member(json, json_get_member(json, toks, "blinding"), "hops");
	assert(hops_tok->size == tal_count(ids));

	json_for_each_arr(i, t, hops_tok) {
		struct secret s;
		struct pubkey pubkey, expected_pubkey;
		u8 *enctlv, *expected_enctlv;
		struct pubkey alias, expected_alias;

		assert(json_to_secret(json,
				      json_get_member(json, t, "ephemeral_privkey"),
				      &s));

		/* First blinding is stated, remainder are derived! */
		if (i == 0) {
			blinding.secret = s;
		} else
			assert(secret_eq_consttime(&blinding.secret, &s));

		assert(pubkey_from_privkey(&blinding, &pubkey));
		json_to_pubkey(json, json_get_member(json, t, "ephemeral_pubkey"),
			       &expected_pubkey);
		assert(pubkey_eq(&pubkey, &expected_pubkey));

		enctlv = enctlv_from_encmsg_raw(tmpctx,
						&blinding,
						&ids[i],
						enctlvs[i],
						&blinding,
						&alias);
		expected_enctlv = json_tok_bin_from_hex(tmpctx,json,
							json_get_member(json, t,
									"encrypted_data"));
		assert(memeq(enctlv, tal_bytelen(enctlv),
			     expected_enctlv, tal_bytelen(expected_enctlv)));

		json_to_pubkey(json, json_get_member(json, t, "blinded_node_id"),
			       &expected_alias);
		assert(pubkey_eq(&alias, &expected_alias));
	}

out:
	common_shutdown();
}