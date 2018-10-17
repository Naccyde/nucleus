#include <nucleus/mm/frames_bitset.h>
/*
uint32_t *frames;
uint32_t nframes;

extern uint32_t placement_address;

#define INDEX_FROM_BIT(a) 	((a)/(8*4))
#define OFFSET_FROM_BIT(a)	((a)%(8*4))

void set_frame(uint32_t frame_addr)
{
	uint32_t frame = frame_addr / 0x1000;
	uint32_t idx = INDEX_FROM_BIT(frame);
	uint32_t off = OFFSET_FROM_BIT(frame);

	frames[idx] |= (0x1 << off);
}

void clear_frame(uint32_t frame_addr)
{
	uint32_t frame = frame_addr / 0x1000;
	uint32_t idx = INDEX_FROM_BIT(frame);
	uint32_t off = OFFSET_FROM_BIT(frame);

	frames[idx] &= ~(0x1 << off);
}

uint32_t test_frame(uint32_t frame_addr)
{
	uint32_t frame = frame_addr / 0x1000;
	uint32_t idx = INDEX_FROM_BIT(frame);
	uint32_t off = OFFSET_FROM_BIT(frame);

	return frames[idx] & (0x1 << off);
}

uint32_t first_frame(void)
{
	uint32_t i, j;

	for (i = 0; i < INDEX_FROM_BIT(nframes); ++i) {
		if (0xffffffff == frames[i])
			continue;
		
		for (j = 0; j < 32; ++j) {
			uint32_t to_test = 0x1 << j;

			if (! (frames[i] & to_test))
				return i * 4 * 8 + j;
		}
	}

	return -1;
}
*/