#include <nucleus/mm/gdt.h>

#include <nucleus/debug.h>

/* GDT flags */
#define GDT_FLAG_REAL_MODE	0x04 // Use 32bits mode when set, 16 otherwise
#define GDT_FLAG_GRANULARITY	0x08 // GDT limits as 32bits addresses

/* GDT access */
#define GDT_ACCESS_RW		0x02 // Segment is readable and writable
#define GDT_ACCESS_GROW_DOWN	0x04 // Direction of the segments growth
#define GDT_ACCESS_EXE		0x08 // Segment is executable
#define GDT_ACCESS_SEGMENT	0x10
#define GDT_ACCESS_RING0	0x00
#define GDT_ACCESS_RING1	0x20
#define GDT_ACCESS_RING2	0x40
#define GDT_ACCESS_RING3	0x60
#define GDT_ACCESS_PRESENT	0x80 // Is segment present ?

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
	gdt[id].access = access | GDT_ACCESS_SEGMENT;
	gdt[id].granularity = ((limit >> 16) & 0x0f) | ((granularity << 4) & 0xc0);
	gdt[id].base_high = (base >> 24) & 0xff;
}

void gdt_init(void)
{
	log("[.] GDT\n");
	gp.limit = (sizeof(struct gdt_entry) * 3) - 1;
	gp.base = (uint32_t)&gdt;

	log("\t[+] Set gates\n");
	gdt_set_gate(0, 0, 0, 0, 0);
	gdt_set_gate(1, 0, 0xFFFFFFFF, GDT_ACCESS_RW | GDT_ACCESS_EXE |
		GDT_ACCESS_PRESENT, GDT_FLAG_REAL_MODE | GDT_FLAG_GRANULARITY);
	gdt_set_gate(2, 0, 0xFFFFFFFF, GDT_ACCESS_RW | GDT_ACCESS_PRESENT,
		GDT_FLAG_REAL_MODE | GDT_FLAG_GRANULARITY);

	log("\t[+] GDT loaded\n");
	gdt_flush(&gp);
}
