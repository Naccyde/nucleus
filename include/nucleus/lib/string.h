#ifndef _NUCLEUS_LIB_STRING_H
#define _NUCLEUS_LIB_STRING_H

#include <nucleus/types.h>
#include <nucleus/bool.h>

size_t strlen(const uint8_t *s);
void strrev(uint8_t *s);
bool itoa(int32_t value, uint8_t *s, size_t len);

#endif
