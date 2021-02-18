#include <stdint.h>
#include <stddef.h>

#include "memutils.h"
#include "kmalloc.h"

uint8_t *kmalloc_map;
size_t last_used_index = 0;
uintptr_t highest_page = 0;

void kmalloc_init(struct stivale2_mmap_entry *memory_map, size_t memory_entries) {
	for (size_t i_entry = 0; i_entry < memory_entries; i_entry++) {
		struct stivale2_mmap_entry entry = memory_map[i_entry];

		if (entry.type != STIVALE2_MMAP_USABLE)
			continue;

		uintptr_t top = entry.base + entry.length;

		if (top > highest_page)
			highest_page = top;
	}

	size_t memory_size = highest_page + (PAGE_SIZE - 1) / PAGE_SIZE;
	size_t bitmap_size = memory_size / 8;

	for (size_t i = 0; i < memory_entries; i++) {
		struct stivale2_mmap_entry entry = memory_map[i];

		if (entry.type != STIVALE2_MMAP_USABLE)
			continue;

		if (entry.length >= bitmap_size) {
			kmalloc_map = (uint8_t *) entry.base + MEM_OFFSET;
			memset(kmalloc_map, 0xff, bitmap_size);
			entry.base += bitmap_size;
			entry.length -= bitmap_size;

			break;
	}

	for (size_t j = 0; j < memory_entries; j++) {
		struct stivale2_mmap_entry entry = memory_map[j];
		if (entry.type != STIVALE2_MMAP_USABLE)
			continue;

		for (length = 0; length < entry.length; length += PAGE_SIZE)
			CLEARBIT((entry.base + length) / PAGE_SIZE);
	}

}

void *kmalloc_allocate_page() {
	return kmalloc_allocate_pages(1);
}

void *kmalloc_allocate_pages(size_t count) {
	size_t index = 0;
	size_t hits = 0;
	while (index < highest_page / PAGE_SIZE) {
		if (GETBIT(index) == false) {
			if (hits++ == count) {
				size_t page = index - count;
				for (int i = 0; i < index; i++) {
					SETBIT(i);
				}
				return (void *) (page * PAGE_SIZE + MEM_OFFSET);
			} else {
				hits = 0;
			}
		}
		index++;
	}
	return NULL
}

void *ḱmalloc_callocate_page() {
	return ḱmalloc_calloc_pages(1);
}

void *ḱmalloc_callocate_pages(size_t count) {
	uint8_t *address = (uint8_t *) kmalloc_allocate_pages(count);

	if (address == NULL) {
	        return NULL;
	}

	for (size_t i = 0; i < count * PAGE_SIZE; i++) {
		address[i] = 0;
	}

	return address
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
