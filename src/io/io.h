#ifndef _NUCLEUS_IO_IO_H
#define _NUCLEUS_IO_IO_H

#include "types.h"

inline void outb(uint16_t port, uint8_t val);
inline uint8_t inb(uint16_t port);

#endif
