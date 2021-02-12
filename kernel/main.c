#include <stdint.h>
#include <stddef.h>
#include <stivale2.h>

#include "arch.h"
#include "panic.h"
#include "paging.h"

static uint8_t stack[4096];

extern uint64_t p4[512];

struct stivale2_header_tag_framebuffer framebuffer_hdr_tag = {
	.tag = {
		.identifier = STIVALE2_HEADER_TAG_FRAMEBUFFER_ID,
		.next = 0
	},
	.framebuffer_width  = 0,
	.framebuffer_height = 0,
	.framebuffer_bpp	= 0
};

__attribute__((section(".stivale2hdr"), used))
struct stivale2_header stivale_hdr = {
	.entry_point = 0,
	.stack = (uintptr_t)stack + sizeof(stack),
	.flags = 0,
	.tags = (uintptr_t)&framebuffer_hdr_tag
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

void kmain(struct stivale2_struct *stivale2_struct) {
	// disable irq because we don't have idt yet
	arch_interrupts_disable();

	// setup paging
	paging_setup();

	struct stivale2_struct_tag_framebuffer *fb_hdr_tag;
	fb_hdr_tag = stivale2_get_tag(stivale2_struct, STIVALE2_STRUCT_TAG_FRAMEBUFFER_ID);

	if (fb_hdr_tag == NULL) {
		panic("Framebuffer not found!");
	}

	uint8_t *fb_addr = (uint8_t *)fb_hdr_tag->framebuffer_addr;
	size_t fb_size = (size_t) (fb_hdr_tag->framebuffer_width * fb_hdr_tag->framebuffer_height * fb_hdr_tag->framebuffer_bpp);

	for (size_t i = 0; i < fb_size; i++) {
		fb_addr[i] = *((uint8_t *) &p4 + i);
	}

	arch_halt();
}
