#include <stdint.h>

#include "arch.h"

#define COM1 0x03f8

void serial_init() {
	arch_outb(COM1 + 1, 0x00);
	arch_outb(COM1 + 3, 0x80);
	arch_outb(COM1 + 0, 0x03);
	arch_outb(COM1 + 1, 0x00);
	arch_outb(COM1 + 3, 0x03);
	arch_outb(COM1 + 2, 0xC7);
}

int serial_received() {
	return arch_inb(COM1 + 5) & 1;
}
 
char serial_read() {
	while (serial_received() == 0);
 
	return arch_inb(COM1);
}

int serial_is_transmit_empty() {
	return arch_inb(COM1 + 5) & 0x20;
}
 
void serial_write(char c) {
	while (serial_is_transmit_empty() == 0);
 
	arch_outb(COM1, c);
}

void serial_write_string(char *string) {
	while (*string) {
		serial_write(*string);
		string++;
	}
}
