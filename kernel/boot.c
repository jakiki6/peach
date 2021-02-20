#include <stivale2.h>

#include <stddef.h>

#include "main.h"
#include "logging.h"

static uint8_t stack[65536];

struct stivale2_header_tag_framebuffer framebuffer_hdr_tag = {
	.tag = {
		.identifier = STIVALE2_HEADER_TAG_FRAMEBUFFER_ID,
		.next = 0
	},
	.framebuffer_width  = 0,
	.framebuffer_height = 0,
	.framebuffer_bpp    = 0
};

__attribute__((section(".stivale2hdr"), used))
struct stivale2_header stivale_hdr = {
	.entry_point = 0,
	.stack = (uint64_t) &stack + sizeof(stack),
	.flags = 0,
	.tags = (uint64_t) &framebuffer_hdr_tag
};

void *stivale2_get_tag(struct stivale2_struct *stivale2_struct, uint64_t id) {
	struct stivale2_tag *current_tag = (void *)stivale2_struct->tags;
	for (;;) {
		if (current_tag == NULL) {
			return NULL;
		}

		if (current_tag->identifier == id) {
			return current_tag;
		}

		current_tag = (void *)current_tag->next;
	}
}

void boot_main(struct stivale2_struct *info) {
	struct stivale2_struct_tag_framebuffer *videoheader = stivale2_get_tag(info, STIVALE2_STRUCT_TAG_FRAMEBUFFER_ID);
	struct stivale2_struct_tag_memmap *memory_map = stivale2_get_tag(info, STIVALE2_STRUCT_TAG_MEMMAP_ID);

	boot_info bootinfo;
	size_t usable_mem = 0;
	uint64_t total_mem = 0;

	for (size_t i = 0; i < memory_map->entries; i++) {
		struct stivale2_mmap_entry *entry = &memory_map->memmap[i];
		total_mem += entry->length;

		if (entry->type == STIVALE2_MMAP_USABLE)
		{
			usable_mem += entry->length;
			bootinfo.memory_top = entry->base + entry->length;
		}

		bootinfo.memory_usable = usable_mem;
		bootinfo.total_memory = total_mem;
	}

	kmain(bootinfo);

	logging_panic("HOW DID YOU GET HERE WTF");
}
