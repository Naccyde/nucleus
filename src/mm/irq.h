#ifndef _NUCLEUS_MM_IRQ_H
#define _NUCLEUS_MM_IRQ_H

#include "mm/isr.h"

void irq_interrupt_handler(struct cpu_state cpu, struct stack_state stack);
void irq_install();

void irq_remap(void);
void irq_uninstall_handler(uint8_t irq_no);
void irq_install_handler(uint8_t irq_no, void (*handler)(struct cpu_state cpu, struct stack_state stack));

#endif
