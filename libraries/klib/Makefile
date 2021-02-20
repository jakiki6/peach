include ../../flags/kernel.mk

TARGET := klib.a

INTERNALCFLAGS := $(INTERNALCFLAGS) \
        -I ../../include/	\
        -I ../../kernel/	\
	-I ../../thirdparty/stivale/ \
	-I ../libprintf/


all: $(OBJ)
	@$(AR) rcs $(TARGET) $(OBJ)

%.o: %.c
	@$(CC) $(CFLAGS) $(INTERNALCFLAGS) -c $< -o $@

%.o: %.asm
	@$(ASM) -f elf64 $< -o $@
