#ifndef _NUCLEUS_IO_IO_H
#define _NUCLEUS_IO_IO_H

#include <nucleus/types.h>

void outb(uint16_t port, uint8_t data);
uint8_t inb(uint16_t port);

#endif
