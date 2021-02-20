TARGET := kernel/kernel.elf
SYMBOLS := kernel/kernel.sym

CC = x86_64-elf-gcc
LD = x86_64-elf-ld
STRIP = x86_64-elf-strip
OBJCOPY = x86_64-elf-objcopy
ASM = nasm

CFLAGS = -Wall -Wextra -O2 -pipe

LDINTERNALFLAGS := \
	-Tkernel/linker.ld   \
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
	-I include/          \
	-I kernel/           \
	-I thirdparty/stivale/

CFILES := $(shell find ./kernel/ -type f -name '*.c')
ASMFILES := $(shell find ./kernel/ -type f -name '*.asm')
OBJ    := $(CFILES:.c=.o) $(ASMFILES:.asm=.o)

.PHONY: all clean

kernel_all: $(TARGET)

$(TARGET): $(OBJ)
	$(LD) $(LDINTERNALFLAGS) $(OBJ) -o $@
	$(OBJCOPY) --only-keep-debug $@ $(SYMBOLS)
#	$(STRIP) $@

%.o: %.c
	$(CC) $(CFLAGS) $(INTERNALCFLAGS) -c $< -o $@

%.o: %.asm
	$(ASM) -f elf64 $< -o $@

kernel_clean:
	rm -rf $(TARGET) $(OBJ) $(SYMBOLS)
