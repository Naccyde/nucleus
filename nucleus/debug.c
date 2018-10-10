#include <nucleus/debug.h>

#define LOG_SERIAL_COM SERIAL_COM1

void log(const uint8_t *s)
{
	serial_write_str(LOG_SERIAL_COM, s);
	vga_write_str(s);
}

void panic(void)
{
	for (;;) ;
}