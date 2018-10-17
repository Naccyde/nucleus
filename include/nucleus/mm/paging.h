#ifndef _NUCLEUS_CPU_PAGING_H
#define _NUCLEUS_CPU_PAGING_H

#include <nucleus/cpu/int/isr.h>
#include <nucleus/types.h>

/*
typedef struct page {
	uint32_t present:1;
	uint32_t rw:1;
	uint32_t user:1;
	uint32_t accessed:1;
	uint32_t dirty:1;
	uint32_t __unused__:7;
	uint32_t frame:20;
} page_t;

typedef struct page_table {
	page_t pages[1024];
} page_table_t;

typedef struct page_directory {
	page_table_t *pages[1024];
	uint32_t tables_phys[1024];
	uint32_t phys_addr;
} page_directory_t;

void paging_init(void);
void switch_page_directory(page_directory_t *dir);
page_t *get_page(uint32_t addr, bool make, page_directory_t *dir);
void page_fault(struct int_machine_state *state);
*/
/*
void load_page_directory(uint32_t *page_dir);
void enable_paging(void);

void paging_init(void);
void clean_tlb(void);
*/

#endif
