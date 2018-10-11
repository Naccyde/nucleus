#include <nucleus/mm/int/isr.h>

#include <nucleus/debug.h>
#include <nucleus/mm/int/idt.h>
#include <nucleus/mm/int/irq.h>

extern void int_handler_0();
extern void int_handler_1();
extern void int_handler_2();
extern void int_handler_3();
extern void int_handler_4();
extern void int_handler_5();
extern void int_handler_6();
extern void int_handler_7();
extern void int_handler_8();
extern void int_handler_9();
extern void int_handler_10();
extern void int_handler_11();
extern void int_handler_12();
extern void int_handler_13();
extern void int_handler_14();
extern void int_handler_15();
extern void int_handler_16();
extern void int_handler_17();
extern void int_handler_18();
extern void int_handler_19();
extern void int_handler_20();
extern void int_handler_21();
extern void int_handler_22();
extern void int_handler_23();
extern void int_handler_24();
extern void int_handler_25();
extern void int_handler_26();
extern void int_handler_27();
extern void int_handler_28();
extern void int_handler_29();
extern void int_handler_30();
extern void int_handler_31();

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

void int_handler(struct int_machine_state *state)
{
	if (state->int_no < 32) {
		log(int_desc[state->int_no]);
		panic();
	}
	
	log("Unknown interrupt called\n");
	panic();
}

void int_install(void)
{
	idt_set_gate(0, (uint32_t)int_handler_0, 0x08, 0x8e);
	idt_set_gate(1, (uint32_t)int_handler_1, 0x08, 0x8e);
	idt_set_gate(2, (uint32_t)int_handler_2, 0x08, 0x8e);
	idt_set_gate(3, (uint32_t)int_handler_3, 0x08, 0x8e);
	idt_set_gate(4, (uint32_t)int_handler_4, 0x08, 0x8e);
	idt_set_gate(5, (uint32_t)int_handler_5, 0x08, 0x8e);
	idt_set_gate(6, (uint32_t)int_handler_6, 0x08, 0x8e);
	idt_set_gate(7, (uint32_t)int_handler_7, 0x08, 0x8e);
	idt_set_gate(8, (uint32_t)int_handler_8, 0x08, 0x8e);
	idt_set_gate(9, (uint32_t)int_handler_9, 0x08, 0x8e);
	idt_set_gate(10, (uint32_t)int_handler_10, 0x08, 0x8e);
	idt_set_gate(11, (uint32_t)int_handler_11, 0x08, 0x8e);
	idt_set_gate(12, (uint32_t)int_handler_12, 0x08, 0x8e);
	idt_set_gate(13, (uint32_t)int_handler_13, 0x08, 0x8e);
	idt_set_gate(14, (uint32_t)int_handler_14, 0x08, 0x8e);
	idt_set_gate(15, (uint32_t)int_handler_15, 0x08, 0x8e);
	idt_set_gate(16, (uint32_t)int_handler_16, 0x08, 0x8e);
	idt_set_gate(17, (uint32_t)int_handler_17, 0x08, 0x8e);
	idt_set_gate(18, (uint32_t)int_handler_18, 0x08, 0x8e);
	idt_set_gate(19, (uint32_t)int_handler_19, 0x08, 0x8e);
	idt_set_gate(20, (uint32_t)int_handler_20, 0x08, 0x8e);
	idt_set_gate(21, (uint32_t)int_handler_21, 0x08, 0x8e);
	idt_set_gate(22, (uint32_t)int_handler_22, 0x08, 0x8e);
	idt_set_gate(23, (uint32_t)int_handler_23, 0x08, 0x8e);
	idt_set_gate(24, (uint32_t)int_handler_24, 0x08, 0x8e);
	idt_set_gate(25, (uint32_t)int_handler_25, 0x08, 0x8e);
	idt_set_gate(26, (uint32_t)int_handler_26, 0x08, 0x8e);
	idt_set_gate(27, (uint32_t)int_handler_27, 0x08, 0x8e);
	idt_set_gate(28, (uint32_t)int_handler_28, 0x08, 0x8e);
	idt_set_gate(29, (uint32_t)int_handler_29, 0x08, 0x8e);
	idt_set_gate(30, (uint32_t)int_handler_30, 0x08, 0x8e);
	idt_set_gate(31, (uint32_t)int_handler_31, 0x08, 0x8e);
}
