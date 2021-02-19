/* Tell the linker that we want the symbol _start to be our entry point */
ENTRY(boot_main)

SECTIONS
{
    __memory_offset = 0xffffffff80000000;
    . = __memory_offset + 2M;

    /* We place the .stivalehdr section containing the header in its own section, */
    /* and we use the KEEP directive on it to make sure it doesn't get discarded. */
    .stivale2hdr ALIGN(4K) : {
        KEEP(*(.stivale2hdr))
    }

    /* Then let's place all the other traditional executable sections afterwards. */
    .text ALIGN(4K) : {
        *(.text*)
    }

    .data ALIGN(4K) : {
        *(.data* .rodata .rodata.*)
    }

    .bss ALIGN(4K) : {
        *(COMMON)
        *(.bss*)
    }

   .text : { *(.text) }
   .data : { *(.data) }
   .bss  : { *(.bss)  }
   /DISCARD/ : { *(.comment) }
}
