#ifndef _NUCLEUS_IO_KB_H
#define _NUCLEUS_IO_KB_H

#include <nucleus/mm/int/isr.h>

void keyboard_handler(struct cpu_state cpu, struct stack_state stack);

#endif
