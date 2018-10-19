#ifndef _NUCLEUS_CPU_TIMER_H
#define _NUCLEUS_CPU_TIMER_H

#include <nucleus/mm/int/isr.h>

void timer_init(void);
void timer_handler(struct machine_state *state);
uint32_t timer_ms_timestamp(void);

#endif
