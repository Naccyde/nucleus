#include <nucleus/mm/paging.h>

#include <nucleus/debug.h>
/*
extern uint32_t *frames;
extern uint32_t nframes;

extern uint32_t placement_address;

#define INDEX_FROM_BIT(a) 	((a)/(8*4))
#define OFFSET_FROM_BIT(a)	((a)%(8*4))

void memclr(void *mem, size_t size)
{
	uint8_t *m = mem;

	for (size_t i = 0; i < size; ++i)
		m[i] = 0;
}

void paging_init(void)
{
	uint32_t mem_end_page = 0x1000000;

	nframes = mem_end_page / 0x1000;
	frames = (uint32_t *)kmalloc(INDEX_FROM_BIT(nframes));
	memclr(frames, INDEX_FROM_BIT(nframes));
}
*/
/*
#define PAGE_DIR_4MB_PAGE	0x80
#define PAGE_DIR_ACCESSED	0x20
#define PAGE_DIR_CACHE_DISABLED	0x10
#define PAGE_DIR_WRITE_THROUGH	0x08
#define PAGE_DIR_USER_PAGE	0x04
#define PAGE_DIR_RW		0x02
#define PAGE_DIR_PRESENT	0x01

#define PAGE_DIR_SIZE 1024
#define FIRST_PAGE_TABLE_SIZE 1024

struct page_directory_entry {
	uint32_t address:20;
	uint32_t _empty:3;
	uint32_t flags:9;
} __attribute__((packed));

struct page_table_entry {
	uint32_t address:20;
	uint32_t _empty:3;
	uint32_t flags:9;
} __attribute__((packed));

static struct page_directory_entry page_dir[PAGE_DIR_SIZE] __attribute__((aligned(4096)));
static struct page_table_entry first_page_table __attribute__((aligned(4096))) = { 0 };

uint32_t page_directory[1024] __attribute__((aligned(4096)));
uint32_t page_table[1024] __attribute__((aligned(4096)));

static void paging_init_identity(void)
{
	for (int i = 0; i < 1024; ++i) {
		page_directory[i] = 0x2;
	}

	for (int i = 0; i < 1024; ++i) {
		page_table[i] = ((i * 0x1000) + 0xc0000000) | 3;
	}

	page_directory[0] = ((unsigned int)page_table) | 3;


	
	for (uint32_t i = 0; i < PAGE_DIR_SIZE; ++i) {
		page_dir[i].address = 0;
		page_dir[i]._empty = 0;
		page_dir[i].flags = PAGE_DIR_USER_PAGE;
	}

	first_page_table.address = 0xc0000000 >> 12;
	first_page_table.flags = PAGE_DIR_4MB_PAGE | PAGE_DIR_ACCESSED | PAGE_DIR_RW | PAGE_DIR_PRESENT;

	page_dir[0].address = (uint32_t)&first_page_table;
	page_dir[0].flags = PAGE_DIR_RW | PAGE_DIR_PRESENT;
	
}


uint32_t page_directory[1024] __attribute__((aligned(4096))) = { 0 };
uint32_t low_page_table[1024] __attribute__((aligned(4096))) = { 0 };
uint32_t ker_page_table[1024] __attribute__((aligned(4096))) = { 0 };

void paging_init(void)
{
	log("[.] Paging!\n");

	for(uint32_t i = 0; i < 1024; i++) {
		page_directory[i] = 0;
		low_page_table[i] = 0;
		ker_page_table[i] = 0;
	}

	for (uint32_t i = 0; i < 256; ++i)
		low_page_table[i] = (i * 4096) | 0x3;
	
	for (uint32_t i = 256; i < 1024; ++i)
		ker_page_table[i] = (0x00100000 + (i * 4096)) | 0x3;

	uint32_t addr = (uint32_t)low_page_table;
	addr = addr - 0xc0000000;
	page_directory[0] = addr | 0x3;
	addr = (uint32_t)ker_page_table;
	addr = addr - 0xc0000000;
	page_directory[768] = addr | 0x3;
	addr = (uint32_t)page_directory;
	addr -= 0xc0000000;
	load_page_directory(addr);
	log("\t[+] Page directory loaded\n");
	enable_paging();
	log("\t[+] Paging enabled\n");
	//clean_tlb();
}
*/