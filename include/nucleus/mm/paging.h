#ifndef _NUCLEUS_CPU_PAGING_H
#define _NUCLEUS_CPU_PAGING_H

#include <nucleus/types.h>

void load_page_directory(uint32_t *page_dir);
void enable_paging(void);

void paging_init(void);

#endif
