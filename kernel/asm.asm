global asm_handler_double_fault
global asm_handler_page_fault

asm_handler_double_fault:
	cli
	hlt
	jmp asm_handler_double_fault

asm_handler_page_fault:
	jmp asm_handler_double_fault
