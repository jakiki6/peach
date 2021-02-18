#include <stddef.h>
#include <stdint.h>

#include "kmalloc.h"
#include "klib.h"

void *kmalloc(size_t size) {
	size_t pages = (size + sizeof(heap_data)) / PAGE_SIZE + 1;

	void *address = kmalloc_allocate_pages(pages);

	heap_data *meta = (heap_data *) address;
	address = address + sizeof(heap_data);

	meta->pages = pages;

	return address;
}

void *kcalloc(size_t size) {
        size_t pages = (size + sizeof(heap_data)) / PAGE_SIZE + 1;

        void *address = ḱmalloc_callocate_pages(pages);

        heap_data *meta = (heap_data *) address;
        address = address + sizeof(heap_data);

        meta->pages = pages;

        return address;
}

void kfree(void *address) {
	address = address - sizeof(heap_data);

	heap_data *meta = (heap_data *) address;

	kmalloc_free_pages(address, meta->pages);
}
