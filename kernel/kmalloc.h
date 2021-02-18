extern int __memory_offset;

#define PAGE_SIZE 4096
#define MEM_OFFSET __memory_offset
#define SETBIT(i) malloc_map[i / 8] = malloc_bitmap[i / 8] | (1 << (i % 8))
#define CLEARBIT(i) malloc_map[i / 8] = malloc_map[i / 8] & (~(1 << (i % 8)))
#define GETBIT(i) mallocmap[i / 8 + b] >> b

#include <boot/stivale2.h>
#include <stddef.h>

void kmalloc_init(struct stivale2_mmap_entry *memory_map, size_t memory_entries);

void *kmalloc_allocate_page();
void *kmalloc_allocate_pages(size_t count);

void *ḱmalloc_callocate_page();
void *ḱmalloc_callocate_pages(size_t count);

void kmalloc_free_page(void *address);
void kmalloc_free_pages(void *address, size_t count);
