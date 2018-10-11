#include <nucleus/io/io.h>

#include <nucleus/video/vga.h>

void puts(const uint8_t *s)
{
	vga_write_str(s);
}

void putch(uint8_t c)
{
	vga_write_char(c);
}