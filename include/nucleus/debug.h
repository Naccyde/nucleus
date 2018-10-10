#ifndef _NUCLEUS_DEBUG_H
#define _NUCLEUS_DEBUG_H

#include <nucleus/types.h>
#include <nucleus/io/serial.h>
#include <nucleus/video/vga.h>

void log(const uint8_t *s);
void panic(void);

#endif
