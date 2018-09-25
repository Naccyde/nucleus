#include "video/vga.h"

void kmain(void)
{
	vga_init();

	const char *s = "Welcome to the Nucleus kernel !\n";

	vga_write_str(s);
}