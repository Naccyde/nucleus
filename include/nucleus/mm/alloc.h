#ifndef _NUCLEUS_MM_ALLOC_H
#define _NUCLEUS_MM_ALLOC_H

#include <nucleus/types.h>
#include <nucleus/bool.h>
#include <nucleus/mm/paging.h>
/*
uint32_t kmalloc_a(size_t size);
uint32_t kmalloc_p(size_t size, uint32_t *phys);
uint32_t kmalloc_ap(size_t size, uint32_t *phys);
uint32_t kmalloc(size_t size);

void alloc_frame(page_t *page, bool is_kernel, bool is_writeable);
void free_frame(page_t *page);
*/
#endif
