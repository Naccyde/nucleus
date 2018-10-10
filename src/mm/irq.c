#include "mm/irq.h"

#include "debug.h"
#include "mm/isr.h"
#include "io/io.h"
#include "mm/idt.h"

extern void irq_interrupt_handler_32(void);
extern void irq_interrupt_handler_33(void);
extern void irq_interrupt_handler_34(void);
extern void irq_interrupt_handler_35(void);
extern void irq_interrupt_handler_36(void);
extern void irq_interrupt_handler_37(void);
extern void irq_interrupt_handler_38(void);
extern void irq_interrupt_handler_39(void);
extern void irq_interrupt_handler_40(void);
extern void irq_interrupt_handler_41(void);
extern void irq_interrupt_handler_42(void);
extern void irq_interrupt_handler_43(void);
extern void irq_interrupt_handler_44(void);
extern void irq_interrupt_handler_45(void);
extern void irq_interrupt_handler_46(void);
extern void irq_interrupt_handler_47(void);

void *irq_routines[16] = { 0 };

void irq_install_handler(uint8_t irq_no, void (*handler)(struct cpu_state cpu, struct stack_state stack))
{
	irq_routines[irq_no] = handler;
}

void irq_uninstall_handler(uint8_t irq_no)
{
	irq_routines[irq_no] = 0;
}

void irq_remap(void)
{
	log("[IRQ] Remap\n");

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

void irq_install()
{
	log("[IRQ] Install\n");

	irq_remap();

	idt_set_gate(32, (uint32_t)irq_interrupt_handler_32, 0x08, 0x8E);
	idt_set_gate(33, (uint32_t)irq_interrupt_handler_33, 0x08, 0x8E);
	idt_set_gate(34, (uint32_t)irq_interrupt_handler_34, 0x08, 0x8E);
	idt_set_gate(35, (uint32_t)irq_interrupt_handler_35, 0x08, 0x8E);
	idt_set_gate(36, (uint32_t)irq_interrupt_handler_36, 0x08, 0x8E);
	idt_set_gate(37, (uint32_t)irq_interrupt_handler_37, 0x08, 0x8E);
	idt_set_gate(38, (uint32_t)irq_interrupt_handler_38, 0x08, 0x8E);
	idt_set_gate(39, (uint32_t)irq_interrupt_handler_39, 0x08, 0x8E);
	idt_set_gate(40, (uint32_t)irq_interrupt_handler_40, 0x08, 0x8E);
	idt_set_gate(41, (uint32_t)irq_interrupt_handler_41, 0x08, 0x8E);
	idt_set_gate(42, (uint32_t)irq_interrupt_handler_42, 0x08, 0x8E);
	idt_set_gate(43, (uint32_t)irq_interrupt_handler_43, 0x08, 0x8E);
	idt_set_gate(44, (uint32_t)irq_interrupt_handler_44, 0x08, 0x8E);
	idt_set_gate(45, (uint32_t)irq_interrupt_handler_45, 0x08, 0x8E);
	idt_set_gate(46, (uint32_t)irq_interrupt_handler_46, 0x08, 0x8E);
	idt_set_gate(47, (uint32_t)irq_interrupt_handler_47, 0x08, 0x8E);
}

void irq_interrupt_handler(struct cpu_state cpu, struct stack_state stack)
{
	log("[IRQ] Called\n");
    /* This is a blank function pointer */
    void (*handler)(struct cpu_state cpu, struct stack_state stack);

    /* Find out if we have a custom handler to run for this
    *  IRQ, and then finally, run it */
    handler = irq_routines[stack.int_no - 32];
    if (handler)
    {
        //handler(r);
    }

    /* If the IDT entry that was invoked was greater than 40
    *  (meaning IRQ8 - 15), then we need to send an EOI to
    *  the slave controller */
    if (stack.int_no >= 40)
    {
        outb(0xA0, 0x20);
    }

    /* In either case, we need to send an EOI to the master
    *  interrupt controller too */
    outb(0x20, 0x20);
}
