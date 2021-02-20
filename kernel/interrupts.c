#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "interrupts.h"
#include "arch.h"
#include "gdt.h"

extern void asm_handler_double_fault();
extern void asm_handler_page_fault();

idt_desc desc = { 0 };
idt_entry entries[256] = { 0 };

void register_interrupt(uint64_t handler, uint8_t number, bool user) {
	idt_entry *entry = &(entries[number]);
	entry->offset_1 = handler & 0xffff000000000000 >> 48;
	entry->offset_2 = handler & 0x0000ffff00000000 >> 32;
	entry->offset_3 = handler & 0x0000000fffffffff >> 0;

	if (user) {
		entry->selector = CS_USER;
	} else {
		entry->selector = CS_KERNEL;
	}
}

void interrupts_init() {
	register_interrupt((uint64_t) &asm_handler_double_fault, 0x08, false);
	register_interrupt((uint64_t) &asm_handler_page_fault, 0x0e, false);

	desc.limit = sizeof(entries) - 1;
	desc.base = (uint64_t) &entries;

	arch_lidt((uint64_t) &desc);
}
