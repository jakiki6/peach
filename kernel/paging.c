#include <stdint.h>

#include "logging.h"
#include "kmalloc.h"
#include "klib.h"
#include "paging.h"

page_map *paging_new_pagemap() {
	page_map *pagemap = (page_map *) kcalloc(sizeof(page_map));

	pagemap->pml4 = kmalloc_callocate_page();

	return pagemap;
}
static uint64_t *get_next_level(uint64_t *current, uint16_t index)
{
	uint64_t ret;
	if (current[index] & 0x1) {
		ret = current[index] & ~((uint64_t) 0xfff);
	} else {
		ret = (uint64_t *) kmalloc_callocate_page();
		current[index] = ret | 0b11;
	}

	return (uint64_t *) ret;
}

void paging_map_page(page_map *pagemap, uint64_t physical_address, uint64_t virtual_address, uint64_t flags) {
	uint64_t level4 = (virtual_address >> 39) & 0x1FF;
	uint64_t level3 = (virtual_address >> 30) & 0x1FF;
	uint64_t level2 = (virtual_address >> 21) & 0x1FF;
	uint64_t level1 = (virtual_address >> 12) & 0x1FF;

	uint64_t *pml4, *pml3, *pml2, *pml1;

	pml4 = (void *) pagemap->pml4;

	pml3 = get_next_level(pml4, level4);
	if (!pml3) {
		logging_panic("paging: pml3 is null");
	}

        pml2 = get_next_level(pml3, level3);
        if (!pml2) {
                logging_panic("paging: pml2 is null");
        }

	pml1 = get_next_level(pml2, level2);
        if (!pml1) {
                logging_panic("paging: pml1 is null");
        }

	pml1[level1] = physical_address | flags;
}

void paging_init() {
	page_map *kernel_map = paging_new_pagemap();

	for (uint64_t i = 0; i < 0x10000000; i += PAGE_SIZE) {
		paging_map_page(kernel_map, i, i + MEM_OFFSET, 0b11);
	}

	arch_set_cr3(kernel_map->pml4);
}
