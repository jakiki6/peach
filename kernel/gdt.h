#include <stdint.h>

#define CS_KERNEL 0x08
#define DS_KERNEL 0x10
#define CS_USER 0x18
#define DS_USER 0x20

typedef struct {
        uint16_t limit;
        uint64_t base;
} __attribute__((packed)) gdt_desc;

typedef struct {
	uint16_t base_0_15;
	uint16_t limit_0_15;
	uint8_t base_24_31;
	uint8_t flags_limit_16_19;
	uint8_t access_byte;
	uint8_t base_16_23;
} __attribute__((packed)) gdt_entry;

void gdt_init();
