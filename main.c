// kuznechik.c
// 04-Jan-15  Markku-Juhani O. Saarinen <mjos@iki.fi>

// main() for testing

#include <stdio.h>
#include "kuznechik.h"

int main(int argc, char **argv)
{	
	const uint8_t testvec_key[32] = {
		0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 
		0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 
		0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10, 
		0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF	
	};
	const uint8_t testvec_pt[16] = {
		0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x00, 
		0xFF, 0xEE, 0xDD, 0xCC, 0xBB, 0xAA, 0x99, 0x88
	};
	const uint8_t testvec_ct[16] = { 
		0x7F, 0x67, 0x9D, 0x90, 0xBE, 0xBC, 0x24, 0x30, 
		0x5A, 0x46, 0x8D, 0x42, 0xB9, 0xD4, 0xED, 0xCD
	};
	
	int i;
	kuz_ctx ctx;
	w128_t x;
		
	kuz_key(&ctx, testvec_key);
	
	for (i = 0; i < 10; i++) {	
		printf("K_%d\t= %016lX%016lX\n", 
			i + 1, ctx.k[i].q[1], ctx.k[i].q[0]);
	}

	for (i = 0; i < 16; i++)
		x.b[i] = testvec_pt[15 - i];

	printf("PT\t= %016lX%016lX\n", x.q[1], x.q[0]);

	kuz_enc(&ctx, &x);

	printf("CT\t= %016lX%016lX\n", x.q[1], x.q[0]);

	for (i = 0; i < 16; i++) {
		if(testvec_ct[i] != x.b[15 - i]) {
			fprintf(stderr, "Encryption fail with kuz_enc_8bit().\n");
			return -1;
		}
	}

	kuz_dec(&ctx, &x);

	printf("PT\t= %016lX%016lX\n", x.q[1], x.q[0]);
	
		for (i = 0; i < 16; i++) {
		if(testvec_pt[i] != x.b[15 - i]) {
			fprintf(stderr, "Decryption fail with kuz_dec_8bit().\n");
			return -2;
		}
	}
	
	printf("OK!\n");
	
	return 0;
}


