#include "video/vga.h"
#include "io/serial.h"
#include "debug.h"

void kmain(void)
{
	vga_init();
	serial_init_all();
	const char *s = "Welcome to the Nucleus kernel !\n";
	log(s);
}