#include <stdint.h>

#include "gdt.h"
#include "arch.h"

extern int __memory_offset;

static gdt_desc desc = { 0 };
static gdt_entry entries[5] = { 0 };

gdt_entry gdt_create_entry(uint8_t access_byte) {
	gdt_entry entry = { 0 };
	entry.limit_0_15 = (uint16_t) 0xffff;
	entry.flags_limit_16_19 = (uint8_t) (0x0f | (0b0010 << 4));
	entry.access_byte = access_byte;

	return entry;
}

void gdt_init() {
	entries[1] = gdt_create_entry(0b10011010);	// code for kernel
	entries[2] = gdt_create_entry(0b10010010);	// data for kernel
        entries[3] = gdt_create_entry(0b11111010);	// code for userspace
        entries[4] = gdt_create_entry(0b11110010);	// data for userspace

	desc.limit = sizeof(entries) - 1;
	desc.base = (uint64_t) &entries;

	arch_lgdt((uint64_t) &desc);
	arch_set_code_segment(CS_KERNEL);
	arch_set_data_segments(DS_KERNEL);
}
