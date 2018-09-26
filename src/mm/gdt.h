#ifndef _NUCLEUS_MM_GDT_H
#define _NUCLEUS_MM_GDT_H

#include "types.h"

void setup_gdt(void);
void gdt_flush(struct gdt *gdt);

#endif
