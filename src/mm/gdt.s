; Set symbols visible outside
global gdt_flush

; gdt_flush - Load the GDT
; stack: [esp + 4] GDT address 
;	 [esp    ] Return address
gdt_flush:
	mov eax, [esp + 4]
	lgdt [eax]
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x08:flush
flush:
	ret
