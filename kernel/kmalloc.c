#include <stdint.h>
#include <stddef.h>
#include <klib/klib.h>
#include <klib/memutils.h>

#include <macros.h>

#include "kmalloc.h"

static uint8_t *kmalloc_map;
size_t last_used_index = 0;
uint64_t highest_page = 0;

void kmalloc_init(struct stivale2_mmap_entry *memory_map, size_t memory_entries) {
	for (size_t i_entry = 0; i_entry < memory_entries; i_entry++) {
		struct stivale2_mmap_entry entry = memory_map[i_entry];

		if (entry.type != STIVALE2_MMAP_USABLE)
			continue;

		uint64_t top = entry.base + entry.length;

		if (top > highest_page)
			highest_page = top;
	}

	size_t memory_size = highest_page + (PAGE_SIZE - 1) / PAGE_SIZE;
	size_t bitmap_size = memory_size / 8;

	log("kmalloc bitmap size: 0x%llx", bitmap_size);

	for (size_t i = 0; i < memory_entries; i++) {
		struct stivale2_mmap_entry entry = memory_map[i];

		if (entry.type != STIVALE2_MMAP_USABLE)
			continue;


		if (entry.length >= bitmap_size) {
			kmalloc_map = (uint8_t *) entry.base + MEM_OFFSET;
			for (uint8_t *ptr = kmalloc_map; (size_t) ptr < bitmap_size; ptr++) {
				*ptr = 0xff;
			}
			entry.base += bitmap_size;
			entry.length -= bitmap_size;

			break;
		}
	}

	log("kmalloc usable memory:");

	for (size_t j = 0; j < memory_entries; j++) {
		struct stivale2_mmap_entry entry = memory_map[j];
		if (entry.type != STIVALE2_MMAP_USABLE)
			continue;

		for (size_t length = 0; length < entry.length; length += PAGE_SIZE)
			CLEARBIT((entry.base + length) / PAGE_SIZE);

		log("\tbase: 0x%llx length 0x%llx", entry.base, entry.length);
	}

	log("kmalloc init:\n\tkmalloc map: 0x%llx\n\thighest page: 0x%llx", (uint64_t) kmalloc_map, highest_page);
}

void *kmalloc_allocate_page() {
	return kmalloc_allocate_pages(1);
}

void *kmalloc_allocate_pages(size_t count) {
	size_t index = last_used_index;
	size_t runs = 0;
	size_t hits = 0;
	while (runs < (highest_page - MEM_OFFSET) / PAGE_SIZE) {
		if (GETBIT(index) == false) {
			if (hits++ == count) {
				size_t page = (index - count) % ((highest_page - MEM_OFFSET) / PAGE_SIZE);
				for (size_t i = 0; i < ((index - last_used_index) % ((highest_page - MEM_OFFSET) / PAGE_SIZE)); i++) {
					SETBIT(i + page);
				}
				//debug("allocated page at address %llx", page * PAGE_SIZE + MEM_OFFSET);
				last_used_index = index;
				return (void *) (page * PAGE_SIZE + MEM_OFFSET);
			}
		} else {
			hits = 0;
		}
		index++;
		index = index % ((highest_page - MEM_OFFSET) / PAGE_SIZE);
	}

	last_used_index = index;
	return (void *) 0;
}

void *kmalloc_callocate_page() {
	return kmalloc_callocate_pages(1);
}

void *kmalloc_callocate_pages(size_t count) {
	uint8_t *address = (uint8_t *) kmalloc_allocate_pages(count);

	if (address == NULL) {
	        return NULL;
	}

	memset(address, 0, count * PAGE_SIZE);

	return address;
}

void kmalloc_free_page(void *address) {
	kmalloc_free_pages(address, 1);
}

void kmalloc_free_pages(void *address, size_t count) {
	uint64_t start_page = (uint64_t) address / PAGE_SIZE;

	for (size_t i = start_page; i < start_page + count; i++) {
		CLEARBIT(i);
	}
}

uint8_t *kmalloc_get_map() {
	return kmalloc_map;
}
