#ifndef _NUCLEUS_IO_SERIAL_H
#define _NUCLEUS_IO_SERIAL_H

#include "bool.h"

#define SERIAL_COM1	0x3f8
#define SERIAL_COM2	0x2f8
#define SERIAL_COM3	0x3e8
#define SERIAL_COM4	0x2e8

void serial_init_all(void);
void serial_write(uint16_t com, uint8_t *d, size_t len);
void serial_write_str(uint16_t com, uint8_t *s);

#endif
