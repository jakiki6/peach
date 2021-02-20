#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "kmalloc.h"
#include "klib.h"
#include "logging.h"
#include "printf.h"

char print_buffer[512] = { 0 };

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

        void *address = kmalloc_callocate_pages(pages);

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

void panic(const char* format, ...) {
	va_list args;
	va_start(args, format);
	sprintf((char *) &print_buffer, format, args);
	va_end(args);
	logging_panic((char *) &print_buffer);
}

void log(const char* format, ...) {
        va_list args;  
        va_start(args, format);
        sprintf((char *) &print_buffer, format, args);
        va_end(args);
        logging_log((char *) &print_buffer);
}

void debug(const char* format, ...) {
        va_list args;  
        va_start(args, format);
        sprintf((char *) &print_buffer, format, args);
        va_end(args);
        logging_debug((char *) &print_buffer);
}
