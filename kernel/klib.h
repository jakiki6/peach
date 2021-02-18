#include <stddef.h>

typedef struct {
        size_t pages;
} heap_data;

void *kmalloc(size_t size);
void *kcalloc(size_t size);
void kfree(void *address);
