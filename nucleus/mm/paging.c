#include <nucleus/mm/paging.h>

#include <nucleus/debug.h>

uint32_t page_directory[1024] __attribute__((aligned(4096)));
uint32_t page_table[1024] __attribute__((aligned(4096)));

void paging_init(void)
{
	log("[.] Paging!\n");

	for (int i = 0; i < 1024; ++i) {
		page_directory[i] = 0x2;
	}
	log("\t[+] Page directory filled\n");

	for (int i = 0; i < 1024; ++i) {
		page_table[i] = (i * 0x1000) | 3;
	}
	log("\t[+] First page table filled\n");

	page_directory[0] = ((unsigned int)page_table) | 3;

	load_page_directory(&page_directory[0]);
	log("\t[+] Page directory loaded\n");
	enable_paging();
	log("\t[+] Paging enabled\n");
}
