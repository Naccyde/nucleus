#include "debug.h"

#define LOG_SERIAL_COM SERIAL_COM1

void log(const char *s)
{
	serial_write_str(LOG_SERIAL_COM, s);
}