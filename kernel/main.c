#include <stdint.h>
#include <stddef.h>

#include "arch.h"
#include "panic.h"
#include "paging.h"
#include "kmalloc.h"
#include "boot.h"
#include "interrupts.h"
#include "gdt.h"

void kmain(boot_info handover) {
	// disable irq because we don't have idt yet
	arch_interrupts_disable();

	// init gdt
	gdt_init();

	// init interrupts
	interrupts_init();

	// init kmalloc
	kmalloc_init(handover.memory_map->memmap, handover.memory_entries);

	// setup paging
	paging_init();

	for (;;);
}
