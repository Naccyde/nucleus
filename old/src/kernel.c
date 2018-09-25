#include "video/vga.h"
#include "debug.h"

void kinit(void);

void kmain(void)
{
	kinit();

	vga_write_str("Nucleus kernel\n");

	return;
}

void kinit(void)
{
	vga_init();
}
