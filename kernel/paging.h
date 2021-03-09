#include <stdint.h>

#define HIGH_OFFSET 0xffff800000000000

typedef struct {
	uint64_t *pml4;
} page_map __attribute__((aligned(4096)));


page_map *paging_new_pagemap();

void paging_map_page(page_map *pagemap, uint64_t physical_address, uint64_t virtual_address, uint64_t flags);

void paging_init();
