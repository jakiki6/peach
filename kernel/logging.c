#include "arch.h"
#include "serial.h"

void logging_debug(char *msg) {
        serial_write_string("debug: ");
        serial_write_string(msg);
        serial_write_string("\n");
}

void logging_log(char *msg) {
	serial_write_string("log: ");
        serial_write_string(msg);
        serial_write_string("\n");
}

void logging_panic(char *msg) {
	serial_write_string("panic: ");
	serial_write_string(msg);
	serial_write_string("\n");

	arch_reboot();
}
