include ../../flags/kernel.mk

TARGET := libprintf.a

INTERNALCFLAGS := $(INTERNALCFLAGS) \
        -I ../../include/	\
        -I ../../kernel/

all: $(OBJ)
	@$(AR) rcs $(TARGET) $(OBJ)

%.o: %.c
	@$(CC) $(CFLAGS) $(INTERNALCFLAGS) -c $< -o $@ -DPRINTF_DISABLE_SUPPORT_FLOAT=1 -DPRINTF_DISABLE_SUPPORT_EXPONENTIAL=1

%.o: %.asm
	@$(ASM) -f elf64 $< -o $@
