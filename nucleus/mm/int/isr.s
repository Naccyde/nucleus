extern int_handler
extern irq_handler

; no_error_code_int_handler
; Macro used to define an interrupt handler which doesn't set an error code
%macro no_error_code_int_handler 1
global int_handler_%1
int_handler_%1:
	cli
	push dword 0
	push dword %1
	jmp int_handler_stub
%endmacro

; error_code_int_handler
; Macro used to define an interrupt handler which does set an error code
%macro error_code_int_handler 1
global int_handler_%1
int_handler_%1:
	cli
	push dword %1
	jmp int_handler_stub
%endmacro

; irq_handler
; Macro used to define an interrupt request handler
%macro irq_handler 1
global irq_handler_%1
irq_handler_%1:
	cli
	push dword 0
	push dword %1
	jmp irq_handler_stub
%endmacro

int_handler_stub:
	pushad
	mov eax, esp
	push eax
	
	call int_handler;

	pop eax
	popad
	add esp, 8

	iret

irq_handler_stub:
	pushad
	mov eax, esp
	push eax

	call irq_handler;

	pop eax
	popad
	add esp, 8

	iret

global sti
sti:
	sti
	ret

no_error_code_int_handler 0
no_error_code_int_handler 1
no_error_code_int_handler 2
no_error_code_int_handler 3
no_error_code_int_handler 4
no_error_code_int_handler 5
no_error_code_int_handler 6
error_code_int_handler 7
no_error_code_int_handler 8
error_code_int_handler 9
error_code_int_handler 10
error_code_int_handler 11
error_code_int_handler 12
error_code_int_handler 13
no_error_code_int_handler 14
no_error_code_int_handler 15
error_code_int_handler 16
no_error_code_int_handler 17
no_error_code_int_handler 18
no_error_code_int_handler 19
no_error_code_int_handler 20
no_error_code_int_handler 21
no_error_code_int_handler 22
no_error_code_int_handler 23
no_error_code_int_handler 24
no_error_code_int_handler 25
no_error_code_int_handler 26
no_error_code_int_handler 27
no_error_code_int_handler 28
no_error_code_int_handler 29
no_error_code_int_handler 30
no_error_code_int_handler 31
irq_handler 32
irq_handler 33
irq_handler 34
irq_handler 35
irq_handler 36
irq_handler 37
irq_handler 38
irq_handler 39
irq_handler 40
irq_handler 41
irq_handler 42
irq_handler 43
irq_handler 44
irq_handler 45
irq_handler 46
irq_handler 47
