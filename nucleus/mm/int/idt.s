global load_idt

; load_idt - Load the IDT
; stack: [esp + 4] IDT address
;	 [esp    ] Return address
load_idt:
	mov eax, [esp + 4]
	lidt [eax]
	ret
