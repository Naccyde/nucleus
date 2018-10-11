#ifndef _NUCLEUS_MM_INT_IDT_H
#define _NUCLEUS_MM_INT_IDT_H

#include <nucleus/types.h>

void idt_init(void);
void idt_init_all(void);
void idt_set_gate(uint8_t id, uint32_t isr, uint16_t segment, uint8_t access);

#endif
