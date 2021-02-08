#include <arch.h>

void panic(char *msg) {
	arch_reboot();
}
