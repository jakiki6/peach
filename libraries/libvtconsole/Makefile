include ../../flags/kernel.mk

TARGET := libvtconsole.a

INTERNALCFLAGS := $(INTERNALCFLAGS) \
        -I ../../include/	\
	-I ../

all: $(OBJ)
	@$(AR) rcs $(TARGET) $(OBJ)

%.o: %.c
	@$(CC) $(CFLAGS) $(INTERNALCFLAGS) -c $< -o $@

%.o: %.asm
	@$(ASM) -f elf64 $< -o $@
