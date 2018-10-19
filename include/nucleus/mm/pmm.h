#ifndef _NUCLEUS_MM_PMM_H
#define _NUCLEUS_MM_PMM_H

#include <nucleus/types.h>

void pmm_set_frame(uint32_t frame_addr);
void pmm_clear_frame(uint32_t frame_addr);
bool pmm_test_frame(uint32_t frame_addr);
uint32_t pmm_get_free_frame(void);

#endif
