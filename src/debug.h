#ifndef _NUCLEUS_DEBUG_H
#define _NUCLEUS_DEBUG_H

#include "types.h"
#include "io/serial.h"
#include "video/vga.h"

void log(const uint8_t *s);
void panic(void);

#endif
