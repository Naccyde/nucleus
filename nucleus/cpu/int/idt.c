#include <nucleus/cpu/int/idt.h>

#include <nucleus/cpu/int/isr.h>

struct idt_entry {
	uint16_t isr_low;
	uint16_t segment;
	uint8_t reserved;
	uint8_t access;
	uint16_t isr_high;
} __attribute__((packed));

struct idt_ptr {
	uint16_t limit;
	uint32_t base;
} __attribute__((packed));

struct idt_entry idt[256] = { 0 };
struct idt_ptr idtp;

extern void load_idt(struct idt_ptr *p);

void idt_init(void)
{
    	idtp.limit = (sizeof (struct idt_entry) * 256) - 1;
   	idtp.base = (uint32_t)&idt;

	// TODO: set macro for IDT entry flags

	load_idt(&idtp);
}

void idt_init_all(void)
{
	log("[.] IDT\n");

	int_install();
	irq_install();

	idt_init();
	sti();
}

void idt_set_gate(uint8_t id, uint32_t isr, uint16_t segment, uint8_t access)
{
	idt[id].isr_low = isr & 0x0000ffff;
	idt[id].isr_high = (isr & 0xffff0000) >> 16;
	idt[id].reserved = 0;
	idt[id].access = access;
	idt[id].segment = segment;
}
