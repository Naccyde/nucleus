#ifndef _NUCLEUS_MM_INT_IRQ_H
#define _NUCLEUS_MM_INT_IRQ_H

#include <nucleus/mm/int/isr.h>

void irq_install(void);
void irq_handler(struct int_machine_state *state);

void irq_uninstall_handler(uint8_t irq_no);
void irq_install_handler(uint8_t irq_no, void (*handler)(struct int_machine_state *state));

#endif
