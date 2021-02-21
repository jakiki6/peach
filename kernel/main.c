#include <stdint.h>
#include <stddef.h>
#include <klib/klib.h>
#include <klib/memutils.h>

#include "arch.h"
#include "paging.h"
#include "kmalloc.h"
#include "boot.h"
#include "interrupts.h"
#include "gdt.h"
#include "serial.h"

void kmain(boot_info handover) {
	// disable irq because we don't have idt yet
	arch_interrupts_disable();

	module("boot");

	// setup serial in case of a panic
	serial_init();

	// init gdt
	gdt_init();

	// init interrupts
	interrupts_init();

	// init kmalloc
	kmalloc_init(handover.memory_map->memmap, handover.memory_entries);

	// setup paging
	paging_init();

	log("Boot completed");
	module("kernel");

	for (;;);
}
