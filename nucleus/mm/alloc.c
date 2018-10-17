#include <nucleus/mm/alloc.h>

#include <nucleus/lib/stdlib.h>
#include <nucleus/mm/frames_bitset.h>
/*
uint32_t placement_address = 0;

static uint32_t kmalloc_int(size_t size, bool align, uint32_t *phys)
{
	uint32_t tmp = 0;
	
	if (align && (placement_address & 0xfffff000)) {
		placement_address &= 0xfffff000;
		placement_address += 0x1000;
	}

	if (phys)
		*phys = placement_address;

	placement_address += size;

	return tmp;
}

uint32_t kmalloc_a(size_t size)
{
	return kmalloc_int(size, true, NULL);
}

uint32_t kmalloc_p(size_t size, uint32_t *phys)
{
	return kmalloc_int(size, false, phys);
}

uint32_t kmalloc_ap(size_t size, uint32_t *phys)
{
	return kmalloc_int(size, true, phys);
}

uint32_t kmalloc(size_t size)
{
	return kmalloc_int(size, false, NULL);
}

void alloc_frame(page_t *page, bool is_kernel, bool is_writeable)
{
	if (0 != page->frame)
		return;
	
	uint32_t idx = first_frame();
	if ((uint32_t)-1 == idx) {
		log("No free frame!\n");
		panic();
	}

	set_frame(idx * 0x1000);
	page->present = 1;
	page->rw = is_writeable;
	page->user = ! is_kernel;
	page->frame = idx;
}

void free_frame(page_t *page)
{
	uint32_t frame;

	if (! (frame = page->frame))
		return;

	clear_frame(frame);
	page->frame = 0;
}
*/