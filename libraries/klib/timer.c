#include <stdint.h>
#include <kernel/arch.h>


#include "klib.h"

uint64_t timer_start() {
	return arch_rdtsc();
}

void timer_end(uint64_t start_time) {
	log("timer took %llu ticks", arch_rdtsc() - start_time);
}
