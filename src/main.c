#include "video/vga.h"
#include "io/serial.h"
#include "debug.h"
#include "mm/gdt.h"
#include "mm/idt.h"
#include "mm/isr.h"

void kmain(void)
{
	vga_init();
	serial_init_all();

	const uint8_t *s = (const uint8_t *)"Welcome to the Nucleus kernel !\n";
	log(s);

	setup_gdt();
	isrs_install();
	idt_init();

	int a = 2;
	a /= 0;

}