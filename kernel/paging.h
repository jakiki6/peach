#include <stdint.h>

static uint64_t p4[512] __attribute__((aligned(4096)));

void paging_setup();
