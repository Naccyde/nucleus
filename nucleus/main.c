#include <nucleus/types.h>
#include <nucleus/video/vga.h>
#include <nucleus/io/serial.h>
#include <nucleus/debug.h>
#include <nucleus/mm/gdt.h>
#include <nucleus/mm/int/idt.h>
#include <nucleus/mm/int/isr.h>
#include <nucleus/mm/int/irq.h>
#include <nucleus/io/kb.h>

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

	irq_install_handler(1, &keyboard_handler);

	log("All setup!\n");
	__asm__ __volatile__ ("sti");
	for (;;);
}