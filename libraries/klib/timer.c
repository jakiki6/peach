#include <stdint.h>

#include "klib.h"
#include "arch.h"

uint64_t timer_start() {
	return arch_rdtsc();
}

void timer_end(uint64_t start_time) {
	log("timer took %llu ticks", arch_rdtsc() - start_time);
}
