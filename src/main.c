#include "video/vga.h"
#include "io/serial.h"
#include "debug.h"
#include "mm/gdt.h"
#include "mm/idt.h"
#include "mm/isr.h"
#include "mm/irq.h"

void kmain(void)
{
	vga_init();
	serial_init_all();

	const uint8_t *s = (const uint8_t *)"Welcome to the Nucleus kernel !\n";
	log(s);

	setup_gdt();
	irq_install();
	isrs_install();
	idt_init();
	log("All setup!\n");
	/*int a = 2;
	a /= 0;*/
	__asm__ __volatile__ ("sti");
	for (;;);

}