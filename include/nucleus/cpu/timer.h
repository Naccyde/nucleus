#ifndef _NUCLEUS_CPU_TIMER_H
#define _NUCLEUS_CPU_TIMER_H

#include <nucleus/mm/int/isr.h>

void timer_init(void);
void timer_handler(struct int_machine_state *state);

#endif
