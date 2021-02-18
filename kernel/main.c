#include <stdint.h>
#include <stddef.h>

#include "arch.h"
#include "panic.h"
#include "paging.h"
#include "kmalloc.h"
#include "boot.h"

void kmain(boot_info handover) {
	// disable irq because we don't have idt yet
	arch_interrupts_disable();

	// init kmalloc
	kmalloc_init();

	// setup paging
	paging_init();

	arch_halt();
}
