include ../../flags/kernel.mk

TARGET := libtinf.a

all: $(OBJ)
	@$(AR) rcs $(TARGET) $(OBJ)

%.o: %.c
	@$(CC) $(CFLAGS) $(INTERNALCFLAGS) -c $< -o $@

%.o: %.asm
	@$(ASM) -f elf64 $< -o $@
