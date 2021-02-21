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

	// log some data
	log("usable memory: %lluMB of %lluMB", handover.memory_usable / 1024 / 1024, handover.total_memory / 1024 / 1024);

	// init gdt
	log("loading gdt");
	gdt_init();

	// init interrupts
	log("loading idt");
	interrupts_init();

	// init kmalloc
	log("init kmalloc");
	kmalloc_init(handover.memory_map->memmap, handover.memory_entries);

	// setup paging
	log("init paging");
	paging_init();

	log("boot completed");
	module("kernel");

	for (;;);
}
