#include <stdint.h>

void arch_outb(uint16_t port, uint8_t val);
void arch_outw(uint16_t port, uint16_t val);

uint8_t arch_inb(uint16_t port);
uint16_t arch_inw(uint16_t port);

void arch_halt();
void arch_reboot();

void arch_interrupts_enable();
void arch_interrupts_disable();
unsigned long arch_are_interrupts_enabled();

void arch_nmi_enable();
void arch_nmi_disable();

void arch_lidt(uint64_t idt);
void arch_lgdt(uint64_t gdt);

void arch_cpuid(int code, uint32_t *a, uint32_t *d);

uint64_t arch_rdtsc();

uint64_t arch_read_cr0();
void arch_write_cr0(uint64_t val);

uint64_t arch_read_cr2();   

uint64_t arch_read_cr4();   
void arch_write_cr4(uint64_t val);

void arch_enable_paging();
void arch_disable_paging();

void arch_set_cr3(uint64_t pointer);
void arch_invalidate_cr3();

void arch_wrmsr(uint64_t msr_id, uint64_t value);
uint64_t arch_rdmsr(uint64_t msr_id);

void arch_set_code_segment(uint8_t value);
void arch_set_data_segments(uint8_t value);
