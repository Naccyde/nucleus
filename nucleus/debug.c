#include <nucleus/debug.h>

#include <nucleus/io/serial.h>
#include <nucleus/io/io.h>

#define LOG_SERIAL_COM SERIAL_COM1

void log(const uint8_t *s)
{
	serial_write_str(LOG_SERIAL_COM, s);
	puts(s);
}

void panic(void)
{
	for (;;) ;
}