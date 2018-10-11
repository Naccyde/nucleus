#include <nucleus/mm/int/irq.h>

#include <nucleus/debug.h>
#include <nucleus/mm/int/isr.h>
#include <nucleus/io/io.h>
#include <nucleus/mm/int/idt.h>
#include <nucleus/io/kb.h>

extern void irq_handler_32(void);
extern void irq_handler_33(void);
extern void irq_handler_34(void);
extern void irq_handler_35(void);
extern void irq_handler_36(void);
extern void irq_handler_37(void);
extern void irq_handler_38(void);
extern void irq_handler_39(void);
extern void irq_handler_40(void);
extern void irq_handler_41(void);
extern void irq_handler_42(void);
extern void irq_handler_43(void);
extern void irq_handler_44(void);
extern void irq_handler_45(void);
extern void irq_handler_46(void);
extern void irq_handler_47(void);

static void *irq_routines[16] = { 0 };

static void irq_remap(void)
{
	// TODO: use macros

	outb(0x20, 0x11);
	outb(0xA0, 0x11);
	outb(0x21, 0x20);
	outb(0xA1, 0x28);
	outb(0x21, 0x04);
	outb(0xA1, 0x02);
	outb(0x21, 0x01);
	outb(0xA1, 0x01);
	outb(0x21, 0x0);
	outb(0xA1, 0x0);
}

void irq_install(void)
{
	irq_remap();

	idt_set_gate(32, (uint32_t)irq_handler_32, 0x08, 0x8E);
	idt_set_gate(33, (uint32_t)irq_handler_33, 0x08, 0x8E);
	idt_set_gate(34, (uint32_t)irq_handler_34, 0x08, 0x8E);
	idt_set_gate(35, (uint32_t)irq_handler_35, 0x08, 0x8E);
	idt_set_gate(36, (uint32_t)irq_handler_36, 0x08, 0x8E);
	idt_set_gate(37, (uint32_t)irq_handler_37, 0x08, 0x8E);
	idt_set_gate(38, (uint32_t)irq_handler_38, 0x08, 0x8E);
	idt_set_gate(39, (uint32_t)irq_handler_39, 0x08, 0x8E);
	idt_set_gate(40, (uint32_t)irq_handler_40, 0x08, 0x8E);
	idt_set_gate(41, (uint32_t)irq_handler_41, 0x08, 0x8E);
	idt_set_gate(42, (uint32_t)irq_handler_42, 0x08, 0x8E);
	idt_set_gate(43, (uint32_t)irq_handler_43, 0x08, 0x8E);
	idt_set_gate(44, (uint32_t)irq_handler_44, 0x08, 0x8E);
	idt_set_gate(45, (uint32_t)irq_handler_45, 0x08, 0x8E);
	idt_set_gate(46, (uint32_t)irq_handler_46, 0x08, 0x8E);
	idt_set_gate(47, (uint32_t)irq_handler_47, 0x08, 0x8E);

	irq_install_handler(1, &keyboard_handler);
}

void irq_handler(struct int_machine_state *state)
{
	void (*handler)(struct int_machine_state *state);

	handler = irq_routines[state->int_no - 32];
	if (handler)
		handler(state);

	/*
	 * If invoked IRQ comes from PIC2, we have to send an EOI to it.
	 */
	if (state->int_no >= 40)
		outb(0xA0, 0x20);

	/* 
	 * In either case, we need to send an EOI to the master interrupt 
	 * controller too
	 */
	outb(0x20, 0x20);
}

void irq_install_handler(uint8_t irq_no, void (*handler)(struct int_machine_state *state))
{
	irq_routines[irq_no] = handler;
}

void irq_uninstall_handler(uint8_t irq_no)
{
	irq_routines[irq_no] = 0;
}
