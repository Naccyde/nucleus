#ifndef _NUCLEUS_CPU_GDT_H
#define _NUCLEUS_CPU_GDT_H

#include <nucleus/types.h>

struct gdt;

void gdt_init(void);
void gdt_flush(struct gdt *gdt);

#endif
