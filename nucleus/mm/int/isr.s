extern interrupt_handler
extern irq_interrupt_handler

%macro no_error_code_interrupt_handler 1
global interrupt_handler_%1
interrupt_handler_%1:
	cli
	push dword 0
	push dword %1
	jmp common_interrupt_handler
%endmacro

%macro error_code_interrupt_handler 1
global interrupt_handler_%1
interrupt_handler_%1:
	cli
	push dword %1
	jmp common_interrupt_handler
%endmacro

%macro irq_interrupt_handler 1
global irq_interrupt_handler_%1
irq_interrupt_handler_%1:
	cli
	push dword 0
	push dword %1
	jmp common_irq_interrupt_handler
%endmacro

common_interrupt_handler:
	pushad

	call interrupt_handler;

	popad

	add esp, 8

	iret

common_irq_interrupt_handler:
	pushad

	call irq_interrupt_handler;

	popad

	add esp, 8

	iret

no_error_code_interrupt_handler 0
no_error_code_interrupt_handler 1
no_error_code_interrupt_handler 2
no_error_code_interrupt_handler 3
no_error_code_interrupt_handler 4
no_error_code_interrupt_handler 5
no_error_code_interrupt_handler 6
error_code_interrupt_handler 7
no_error_code_interrupt_handler 8
error_code_interrupt_handler 9
error_code_interrupt_handler 10
error_code_interrupt_handler 11
error_code_interrupt_handler 12
error_code_interrupt_handler 13
no_error_code_interrupt_handler 14
no_error_code_interrupt_handler 15
error_code_interrupt_handler 16
no_error_code_interrupt_handler 17
no_error_code_interrupt_handler 18
no_error_code_interrupt_handler 19
no_error_code_interrupt_handler 20
no_error_code_interrupt_handler 21
no_error_code_interrupt_handler 22
no_error_code_interrupt_handler 23
no_error_code_interrupt_handler 24
no_error_code_interrupt_handler 25
no_error_code_interrupt_handler 26
no_error_code_interrupt_handler 27
no_error_code_interrupt_handler 28
no_error_code_interrupt_handler 29
no_error_code_interrupt_handler 30
no_error_code_interrupt_handler 31
irq_interrupt_handler 32
irq_interrupt_handler 33
irq_interrupt_handler 34
irq_interrupt_handler 35
irq_interrupt_handler 36
irq_interrupt_handler 37
irq_interrupt_handler 38
irq_interrupt_handler 39
irq_interrupt_handler 40
irq_interrupt_handler 41
irq_interrupt_handler 42
irq_interrupt_handler 43
irq_interrupt_handler 44
irq_interrupt_handler 45
irq_interrupt_handler 46
irq_interrupt_handler 47
