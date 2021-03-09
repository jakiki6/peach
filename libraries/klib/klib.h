#include <stddef.h>

typedef struct {
        size_t pages;
} heap_data;

void *kmalloc(size_t size);
void *kcalloc(size_t size);
void kfree(void *address);

void panic(const char* format, ...);
void log(const char* format, ...);
void debug(const char* format, ...);
void module(char *name);
uint64_t UD(uint64_t num, uint64_t div);
