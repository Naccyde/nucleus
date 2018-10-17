global loader				; ELF entry symbol
extern kmain

MODULEALIGN	equ 1 << 0
MEMINFO		equ 1 << 1
MAGIC_NUMBER	equ 0x1badb002			; Magic number
FLAGS		equ MODULEALIGN | MEMINFO	; Multiboot flags
CHECKSUM	equ -(MAGIC_NUMBER + FLAGS)	; (MAGIC_NUMBER + FLAGS + CHECKSUM = 0)
KERNEL_STACK_SIZE equ 0x4000			; Size of the kernel stack

KERNEL_VIRTUAL_BASE equ 0xc0000000
KERNEL_PAGE_NUMBER equ (KERNEL_VIRTUAL_BASE >> 22)

section .data
align 0x1000
boot_page_directory:
	dd 0x00000083
	times (KERNEL_PAGE_NUMBER - 1) dd 0
	dd 0x00000083
	times (1024 - KERNEL_PAGE_NUMBER - 1) dd 0

section .text				; Start of the text (code) section
align 4					; Align on 4 bytes limit
multiboot_header:
	dd MAGIC_NUMBER
	dd FLAGS
	dd CHECKSUM

STACKSIZE equ 0x4000
loader equ (_loader - 0xc0000000)
global loader

_loader:
	mov ecx, (boot_page_directory - KERNEL_VIRTUAL_BASE)
	mov cr3, ecx

	mov ecx, cr4
	or ecx, 0x00000010
	mov cr4, ecx

	mov ecx, cr0
	or ecx, 0x80000000
	mov cr0, ecx

	lea ecx, [higher_half]
	jmp ecx

higher_half:
	mov dword [boot_page_directory], 0
	invlpg [0]
	mov esp, kernel_stack + KERNEL_STACK_SIZE ; Set esp to end of the stack

	call kmain
	hlt
	
section .bss
align 32
kernel_stack:
	resb KERNEL_STACK_SIZE		; Reserve stack size inside the memory
