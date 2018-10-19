#include <nucleus/mm/pmm.h>

#include <nucleus/debug.h>
#include <nucleus/lib/stdlib.h>

// TODO: Remove to get non-fixed values
#define TODOR_RAM_SIZE_KIB	2147483648
#define TODOR_NB_FRAMES		524288
#define TODOR_NB_FRAMES_ARRAY	16384

#define IDX_FROM_BITS(v) ((v) / 32)
#define OFF_FROM_BITS(v) ((v) % 32)

uint32_t frames[TODOR_NB_FRAMES_ARRAY] = { 0 };
uint32_t nbframes = TODOR_NB_FRAMES;

void pmm_set_frame(uint32_t frame_addr)
{
	uint32_t frame = frame_addr / 0x1000;
	frames[IDX_FROM_BITS(frame)] |= 0x1 << OFF_FROM_BITS(frame);
}

void pmm_clear_frame(uint32_t frame_addr)
{
	uint32_t frame = frame_addr / 0x1000;
	frames[IDX_FROM_BITS(frame)] &= ~(0x1 << OFF_FROM_BITS(frame));
}

bool pmm_test_frame(uint32_t frame_addr)
{
	uint32_t frame = frame_addr / 0x1000;
	return frames[IDX_FROM_BITS(frame)] & (0x1 << OFF_FROM_BITS(frame));
}

uint32_t pmm_get_free_frame(void)
{
	memset(frames, 0xff, TODOR_NB_FRAMES_ARRAY * 4);
	for (uint32_t i = 0; i < IDX_FROM_BITS(nbframes); ++i) {
		if (0xffffffff == frames[i])
			continue;
		
		for (uint8_t j = 0; j < 32; ++j) {
			if (! (frames[i] & (0x1 << j)))
				return (i * 32 + j) * 0x1000;
		}
	}

	panic("No more memory available\n", NULL);
	return 0;
}
