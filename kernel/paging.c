#include <stdint.h>

#include "arch.h"

static uint64_t p4[512] __attribute__((aligned(4096)));
static uint64_t p3[512] __attribute__((aligned(4096)));
static uint64_t p2s[2][512] __attribute__((aligned(4096)));

void paging_setup() {
	arch_invalidate_cr3();
	for (int i = 0; i < 512; i++) {
		p4[i] = 0;
		p3[i] = 0;
		p2s[0][i] = 0;
		p2s[1][i] = 0;
	}

	p4[0] = ((uint64_t) (&p3)) | 0b11;
	p3[0] = ((uint64_t) (&p2s[0])) | 0b11;
	p3[1] = ((uint64_t) (&p2s[1])) | 0b11;

	for (int j = 0; j < 2; j++) {
		for (int i = 0; i < 512; i++) {
			p2s[j][i] = 0x200000 * (512 * j + i) | 0b10000011;
		}
	}

	arch_set_cr3(&p4);
}
