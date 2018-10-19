#include <nucleus/mm/paging.h>

#include <nucleus/debug.h>
#include <nucleus/mm/pmm.h>

typedef struct page {
	uint32_t present	: 1;
	uint32_t rw		: 1;
	uint32_t user		: 1;
	uint32_t accessed	: 1;
	uint32_t dirty		: 1;
	uint32_t unused		: 7;
	uint32_t frame		: 20;
} __attribute__((packed)) page_t;

typedef struct page_table {
	page_t pages[1024];
} __attribute__((packed)) page_table_t;

typedef struct page_directory {
	page_table_t *pages_tables[1024];
	uint32_t pages_tables_phys[1024];
	uint32_t addr_phys;
} page_directory_t;

extern uint8_t kernel_start;
extern uint8_t kernel_end;
uint32_t size = (uint32_t)&kernel_end;

uint32_t page_directory[1024] __attribute__((aligned(4096)));
uint32_t page_table0[1024] __attribute__((aligned(4096)));

void paging_init(void)
{
	pmm_get_free_frame();
	log("[.] Paging!\n");

	for(uint32_t i = 0; i < 1024; i++) {
		page_directory[i] = 0;
		page_table0[i] = 0;
	}

	for (uint32_t i = 0; i < 1024; ++i) {
		page_table0[i] = (i * 4096) | 0x3;
	}
	uint32_t page_table0_addr = (uint32_t)page_table0 - 0xc0000000;
	uint32_t page_directory_addr = (uint32_t)page_directory - 0xc0000000;

	page_directory[768] = page_table0_addr | 0x3;
	enable_paging((uint32_t)page_directory_addr);
}
