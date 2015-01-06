// kuznechik.c
// 04-Jan-15  Markku-Juhani O. Saarinen <mjos@iki.fi>

// main() for testing

#include <stdio.h>
#include <time.h>
#include "kuznechik.h"

// debug print state

void print_w128(w128_t *x)
{
	int i;
	
	for (i = 0; i < 16; i++)
		printf(" %02X", x->b[i]);
	printf("\n");
}

// stub main

void kuz_init();

int main(int argc, char **argv)
{	
	// These are here in Big Endian format, as that seems to be the favored
	// way of representing things. However, it is open if we will have to
	// flip byte order for the final version or not.
	
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
	
	int i, j, n;
	kuz_key_t key;
	w128_t x;
	uint32_t buf[0x100];
	clock_t tim;

	printf("Self-test:\n");
	kuz_init();
			
	kuz_set_encrypt_key(&key, testvec_key);	
	for (i = 0; i < 10; i++) {	
		printf("K_%d\t=", i + 1);
		print_w128(&key.k[i]);
	}

	for (i = 0; i < 16; i++)
		x.b[i] = testvec_pt[i];
	printf("PT\t=");
	print_w128(&x);

	kuz_encrypt_block(&key, &x);

	printf("CT\t=");
	print_w128(&x);

	for (i = 0; i < 16; i++) {
		if (testvec_ct[i] != x.b[i]) {
			fprintf(stderr, "Encryption self-test failure.\n");
			return -1;
		}
	}

	kuz_set_decrypt_key(&key, testvec_key);
	kuz_decrypt_block(&key, &x);

	printf("PT\t=");
	print_w128(&x);
	
	for (i = 0; i < 16; i++) {
		if (testvec_pt[i] != x.b[i]) {
			fprintf(stderr, "Decryption self-test failure.\n");
			return -2;
		}
	}
	
	printf("Self-test OK!\n");
	
	// == Speed Test ==
	
	for (i = 0; i < 0x100; i++)
		buf[i] = i;
	kuz_set_encrypt_key(&key, testvec_key);	

	for (n = 100, tim = 0; tim < 2 * CLOCKS_PER_SEC; n <<= 1) {
		tim = clock();
		for (j = 0; j < n; j++) {
			for (i = 0; i < 0x100; i += 4)
				kuz_encrypt_block(&key, &buf[i]);
		}
		tim = clock() - tim;
		printf("kuz_encrypt_block(): %.3f kB/s (n=%dkB,t=%.3fs)\r",
			((double) CLOCKS_PER_SEC * n) / ((double) tim), 
			n, ((double) tim) / ((double) CLOCKS_PER_SEC));
		fflush(stdout);
	}
	printf("\n");
	
	
	for (i = 0; i < 0x100; i++)
	buf[i] = i;
	kuz_set_decrypt_key(&key, testvec_key);	

	for (n = 100, tim = 0; tim < 2 * CLOCKS_PER_SEC; n <<= 1) {
		tim = clock();
		for (j = 0; j < n; j++) {
			for (i = 0; i < 0x100; i += 4)
				kuz_decrypt_block(&key, &buf[i]);
		}
		tim = clock() - tim;
		printf("kuz_decrypt_block(): %.3f kB/s (n=%dkB,t=%.3fs)\r",
			((double) CLOCKS_PER_SEC * n) / ((double) tim), 
			n, ((double) tim) / ((double) CLOCKS_PER_SEC));
		fflush(stdout);
	}
	printf("\n");
	
	
	return 0;
}


