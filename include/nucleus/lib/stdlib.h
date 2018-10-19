#ifndef _NUCLEUS_LIB_STDLIB_H
#define _NUCLEUS_LIB_STDLIB_H

#include <nucleus/types.h>

#define NULL (void *)0
#define UNUSED(expr) (void)(expr)

void *memset(void *p, uint8_t v, size_t size);

#endif
