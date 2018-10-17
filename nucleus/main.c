#include <nucleus/types.h>
#include <nucleus/video/vga.h>
#include <nucleus/io/serial.h>
#include <nucleus/debug.h>
#include <nucleus/mm/gdt.h>
#include <nucleus/mm/int/idt.h>
#include <nucleus/mm/int/isr.h>
#include <nucleus/mm/int/irq.h>
#include <nucleus/io/kb.h>
#include <nucleus/cpu/timer.h>

void kmain(void)
{
	vga_init();
	serial_init_all();

	const uint8_t *s = (const uint8_t *)"Welcome to the Nucleus kernel !\n";
	log(s);

	gdt_init();
	idt_init_all();
	timer_init();

	log("[+] All setup!\n");
	__asm__ __volatile__ ("sti");

	panic();
}