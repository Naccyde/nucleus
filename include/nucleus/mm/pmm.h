#ifndef _NUCLEUS_MM_PMM_H
#define _NUCLEUS_MM_PMM_H

#include <nucleus/types.h>

inline void pmm_set_frame(uint32_t frame_addr);
inline void pmm_clear_frame(uint32_t frame_addr);
inline bool pmm_test_frame(uint32_t frame_addr);
uint32_t pmm_get_free_frame(void);

#endif
