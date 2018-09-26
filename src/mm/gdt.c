#include "mm/gdt.h"

struct gdt {
	uint16_t limit;
	uint32_t base;
} __attribute__((packed));

struct gdt_entry {
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_mid;
	uint8_t access;
	uint8_t granularity;
	uint8_t base_high;
} __attribute__((packed));

struct gdt_entry gdt[3] = { 0 };
struct gdt gp;

static void gdt_set_gate(int id, uint32_t base, uint32_t limit, uint8_t access,
	uint8_t granularity)
{
	gdt[id].limit_low = limit & 0xffff;
	gdt[id].base_low = base & 0xffff;
	gdt[id].base_mid = (base >> 16) & 0xff;
	gdt[id].access = access;
	gdt[id].granularity = ((limit >> 16) & 0x0f) | (granularity & 0xF0);
	gdt[id].base_high = (base >> 24) & 0xff;
}

void setup_gdt(void)
{
	gp.limit = (sizeof(struct gdt_entry) * 3) - 1;
	gp.base = &gdt;

	gdt_set_gate(0, 0, 0, 0, 0);
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

	gdt_flush(&gp);
}
