#include <stdint.h>

#include "arch.h"

uint64_t p4[512] __attribute__((aligned(4096)));
static uint64_t p3[512] __attribute__((aligned(4096)));
static uint64_t p2s[3][512] __attribute__((aligned(4096)));

void paging_setup() {
	for (int i = 0; i < 512; i++) {
		p4[i] = 0;
		p3[i] = 0;
	}

	p4[0] = ((uint64_t) (&p3)) | 0b11;

	for (int j = 0; j < 3; j++) {
		p3[j] = ((uint64_t) (&(p2s[j]))) | 0b11;
		for (int i = 0; i < 512; i++) {
			p2s[j][i] = 0x200000 * (512 * j + i) | 0b10000011;
		}
	}

	arch_set_cr3(&p4);
}
