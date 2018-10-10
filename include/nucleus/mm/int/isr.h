#ifndef _NUCLEUS_MM_INT_ISR_H
#define _NUCLEUS_MM_INT_ISR_H

#include <nucleus/types.h>

struct cpu_state {
	uint32_t edi;
	uint32_t esi;
	uint32_t ebp;
	uint32_t esp;
	uint32_t ebx;
	uint32_t edx;
	uint32_t ecx;
	uint32_t eax;
} __attribute__((packed));

struct stack_state {
	uint32_t int_no;
	uint32_t error;
	uint32_t eip;
	uint32_t cs;
	uint32_t eflags;
	uint32_t usersp;
	uint32_t ss;
} __attribute__((packed));

void interrupt_handler(struct cpu_state cpu, struct stack_state stack);
void isrs_install(void);

#endif