#include <stdint.h>
#include <stivale2.h>

typedef struct {
	size_t memory_usable;
	size_t total_memory;
	size_t memory_entries;
	uintptr_t memory_top;
	struct stivale2_struct_tag_memmap *memory_map;
  
	uint64_t framebuffer_addr;
	uint16_t framebuffer_width;
	uint16_t framebuffer_height;
	uint16_t framebuffer_pitch;
	uint16_t framebuffer_bpp;
} boot_info;
