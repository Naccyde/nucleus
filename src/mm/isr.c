#include "mm/isr.h"

#include "debug.h"
#include "mm/extern_isr.h"
#include "mm/idt.h"

static const uint8_t *int_desc[] = {
	"Division by zero exception",
	"Debug exception",
	"Non maskable interrupt exception",
	"Breakpoint exception",
	"Into detected overflow exception",
	"Out of bounds exception",
	"Invalid opcode exception",
	"No coprocessors exception",
	"Double fault exception",
	"Coprocessor segment overrun exception",
	"Bad TSS exception",
	"Segment not present exception",
	"Stack fault exception",
	"General protection fault exception",
	"Page fault exception",
	"Unknow interrupt exception",
	"Coprocessor fault exception",
	"Alignment check exception",
	"Machine check exception",
	"Reserved exception",
	"Reserved exception",
	"Reserved exception",
	"Reserved exception",
	"Reserved exception",
	"Reserved exception",
	"Reserved exception",
	"Reserved exception",
	"Reserved exception",
	"Reserved exception",
	"Reserved exception",
	"Reserved exception",
	"Reserved exception",
};

void interrupt_handler(struct cpu_state cpu, struct stack_state stack, uint32_t interrupt)
{
	if (interrupt < 32) {
		log(int_desc[interrupt]);
		panic();
	}
	
	log("Interrupt called\n");
}

void isrs_install(void)
{
	idt_set_gate(0, (uint32_t)interrupt_handler_0, 0x08, 0x8e);
	idt_set_gate(1, (uint32_t)interrupt_handler_1, 0x08, 0x8e);
	idt_set_gate(2, (uint32_t)interrupt_handler_2, 0x08, 0x8e);
	idt_set_gate(3, (uint32_t)interrupt_handler_3, 0x08, 0x8e);
	idt_set_gate(4, (uint32_t)interrupt_handler_4, 0x08, 0x8e);
	idt_set_gate(5, (uint32_t)interrupt_handler_5, 0x08, 0x8e);
	idt_set_gate(6, (uint32_t)interrupt_handler_6, 0x08, 0x8e);
	idt_set_gate(7, (uint32_t)interrupt_handler_7, 0x08, 0x8e);
	idt_set_gate(8, (uint32_t)interrupt_handler_8, 0x08, 0x8e);
	idt_set_gate(9, (uint32_t)interrupt_handler_9, 0x08, 0x8e);
	idt_set_gate(10, (uint32_t)interrupt_handler_10, 0x08, 0x8e);
	idt_set_gate(11, (uint32_t)interrupt_handler_11, 0x08, 0x8e);
	idt_set_gate(12, (uint32_t)interrupt_handler_12, 0x08, 0x8e);
	idt_set_gate(13, (uint32_t)interrupt_handler_13, 0x08, 0x8e);
	idt_set_gate(14, (uint32_t)interrupt_handler_14, 0x08, 0x8e);
	idt_set_gate(15, (uint32_t)interrupt_handler_15, 0x08, 0x8e);
	idt_set_gate(16, (uint32_t)interrupt_handler_16, 0x08, 0x8e);
	idt_set_gate(17, (uint32_t)interrupt_handler_17, 0x08, 0x8e);
	idt_set_gate(18, (uint32_t)interrupt_handler_18, 0x08, 0x8e);
	idt_set_gate(19, (uint32_t)interrupt_handler_19, 0x08, 0x8e);
	idt_set_gate(20, (uint32_t)interrupt_handler_20, 0x08, 0x8e);
	idt_set_gate(21, (uint32_t)interrupt_handler_21, 0x08, 0x8e);
	idt_set_gate(22, (uint32_t)interrupt_handler_22, 0x08, 0x8e);
	idt_set_gate(23, (uint32_t)interrupt_handler_23, 0x08, 0x8e);
	idt_set_gate(24, (uint32_t)interrupt_handler_24, 0x08, 0x8e);
	idt_set_gate(25, (uint32_t)interrupt_handler_25, 0x08, 0x8e);
	idt_set_gate(26, (uint32_t)interrupt_handler_26, 0x08, 0x8e);
	idt_set_gate(27, (uint32_t)interrupt_handler_27, 0x08, 0x8e);
	idt_set_gate(28, (uint32_t)interrupt_handler_28, 0x08, 0x8e);
	idt_set_gate(29, (uint32_t)interrupt_handler_29, 0x08, 0x8e);
	idt_set_gate(30, (uint32_t)interrupt_handler_30, 0x08, 0x8e);
	idt_set_gate(31, (uint32_t)interrupt_handler_31, 0x08, 0x8e);
}
