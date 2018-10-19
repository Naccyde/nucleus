#include <nucleus/lib/stdlib.h>

void *memset(void *p, uint8_t v, size_t size)
{
	uint8_t *_p = p;

	for (size_t i = 0; i < size; ++i)
		*_p++ = v;
	
	return _p;
}
