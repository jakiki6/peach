#include <stdint.h>

void arch_outb(uint16_t port, uint8_t val) {
	asm volatile ("outb %0, %1"::"a"(val), "Nd"(port));
}

void arch_outw(uint16_t port, uint16_t val) { 
        asm volatile ("outw %0, %1"::"a"(val), "Nd"(port));     
}

uint8_t arch_inb(uint16_t port) {
	uint8_t ret;
	asm volatile ("inb %1, %0"
                   : "=a"(ret)
                   : "Nd"(port));
	return ret;
}

uint16_t arch_inw(uint16_t port) {            
        uint16_t ret;
        asm volatile ("inw %1, %0" 
                   : "=a"(ret) 
                   : "Nd"(port)); 
        return ret;
}

void arch_halt() {
	arch_interrupts_disable();
	while (1) {
		asm volatile ("hlt");
	}
}

void arch_reboot() {
	arch_outb(0x0cf9, 0x0e);
	arch_halt();
}

void arch_interrupts_enable() {
        asm volatile("sti");
}

void arch_interrupts_disable() {
	asm volatile("cli");
}

unsigned long arch_are_interrupts_enabled() {
	unsigned long flags;
	asm volatile ("pushf\n\t"
		"pop %0"
		: "=g"(flags));
	return flags & (1 << 9);
}

void arch_nmi_enable() {
	arch_outb(0x70, arch_inb(0x70) & 0x7F);
}
 
void arch_nmi_disable() {
	arch_outb(0x70, arch_inb(0x70) | 0x80);
}

void arch_lidt(uint64_t idt) {
	asm volatile ("lidt (%0)" : : "r"(idt));
}

void arch_lgdt(uint64_t gdt) {
        asm volatile ("lgdt (%0)" : : "r"(gdt));
}


void arch_cpuid(int code, uint32_t *a, uint32_t *d) {
	asm volatile ("cpuid" : "=a"(*a), "=d"(*d) : "0"(code) : "ebx", "ecx");
}

uint64_t arch_rdtsc() {
	uint64_t ret;
	asm volatile ("rdtsc" : "=A"(ret));
	return ret;
}

uint64_t arch_read_cr0() {
	uint64_t val;
	asm volatile ("mov %%cr0, %0" : "=r"(val));
	return val;
}

void arch_write_cr0(uint64_t val) {
	asm volatile ("mov %0, %%cr0" : "=r"(val));
}

uint64_t arch_read_cr2() {    
        uint64_t val;
        asm volatile ("mov %%cr2, %0" : "=r"(val));
        return val;
}

uint64_t arch_read_cr4() {    
        uint64_t val;
        asm volatile ("mov %%cr4, %0" : "=r"(val));
        return val;
}
 
void arch_write_cr4(uint64_t val) {
        asm volatile ("mov %0, %%cr4" : "=r"(val)); 
}

void arch_enable_paging() {
	arch_write_cr0(arch_read_cr0() | (1 << 31));
}

void arch_disable_paging() {
	arch_write_cr0(arch_read_cr0() & ~(1 << 31));
}

void arch_set_cr3(uint64_t pointer) {
	asm volatile ("mov %0, %%cr3" : "=r"(pointer));
}

void arch_invalidate_cr3() {
	asm volatile (
		"mov %cr3, %rax;"
		"mov %rax, %cr3;"
	);
}

void arch_wrmsr(uint64_t msr, uint64_t value) {
	uint32_t low = value & 0xFFFFFFFF;
	uint32_t high = value >> 32;
	asm volatile (
		"wrmsr"
		:
		: "c"(msr), "a"(low), "d"(high)
	);
}

uint64_t arch_rdmsr(uint64_t msr) {
	uint32_t low, high;
	asm volatile (
		"rdmsr"
		: "=a"(low), "=d"(high)
		: "c"(msr)
	);
	return ((uint64_t) high << 32) | low;
}

void arch_set_code_segment(uint8_t value) {
	asm volatile (
		"mov %%cs, %%ax"
		:
		: "a"(value)
	);
}

void arch_set_data_segments(uint8_t value) {
        asm volatile (  
                "mov %%ds, %%ax;"
                "mov %%es, %%ax;"
                "mov %%ss, %%ax;"
                "mov %%fs, %%ax;"
                "mov %%gs, %%ax;"
                :
                : "a"(value)
        );
}