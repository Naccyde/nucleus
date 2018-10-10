global loader				; ELF entry symbol
extern kmain

MAGIC_NUMBER	equ 0x1badb002		; Magic number
FLAGS		equ 0x0			; Multiboot flags
CHECKSUM	equ -MAGIC_NUMBER	; (MAGIC_NUMBER + FLAGS + CHECKSUM = 0)
KERNEL_STACK_SIZE equ 4096		; Size of the kernel stack

section .text				; Start of the text (code) section
align 4					; Align on 4 bytes limit
	dd MAGIC_NUMBER
	dd FLAGS
	dd CHECKSUM

loader:
	mov esp, kernel_stack + KERNEL_STACK_SIZE ; Set esp to end of the stack
	call kmain
.loop:
	jmp .loop

section .bss
align 4
kernel_stack:
	resb KERNEL_STACK_SIZE		; Reserve stack size inside the memory
