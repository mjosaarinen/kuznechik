// kuznechik.h
// 04-Jan-15  Markku-Juhani O. Saarinen <mjos@iki.fi>

#ifndef KUZNECHIK_H
#define KUZNECHIK_H

#include <stdint.h>

// my 128-bit datatype
typedef union {
    uint64_t q[2];
    uint8_t  b[16];
} w128_t;

// cipher context
typedef struct {
	w128_t k[10];		// round keys
} kuz_ctx;

// basic ECB interface

void kuz_key(kuz_ctx *kuz, const uint8_t key[32]);	// key setup
void kuz_enc(kuz_ctx *kuz, w128_t *x);				// encrypt a block
void kuz_dec(kuz_ctx *kuz, w128_t *x);				// decrypt a block

#endif
