#ifndef _NUCLEUS_DEBUG_H
#define _NUCLEUS_DEBUG_H

#include <nucleus/types.h>
#include <nucleus/mm/int/isr.h>

void log(const uint8_t *s);
void panic(const uint8_t *s, struct machine_state *state);

#endif
