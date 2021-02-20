CC = x86_64-elf-gcc
LD = x86_64-elf-ld
STRIP = x86_64-elf-strip
OBJCOPY = x86_64-elf-objcopy
AR = x86_64-elf-ar
ASM = nasm

CFLAGS = -Wall -Wextra -O2 -pipe

LDINTERNALFLAGS := \
        -static              \
        -nostdlib

INTERNALCFLAGS  :=       \
        -I.                  \
        -ffreestanding       \
        -fno-stack-protector \
        -fno-pic             \
        -fno-asynchronous-unwind-tables \
        -mno-80387           \
        -mno-mmx             \
        -mno-3dnow           \
        -mno-sse             \
        -mno-sse2            \
        -mcmodel=large       \
        -mno-red-zone        \

CFILES := $(shell find . -type f -name '*.c')
ASMFILES := $(shell find . -type f -name '*.asm')
OBJ    := $(CFILES:.c=.o) $(ASMFILES:.asm=.o)
