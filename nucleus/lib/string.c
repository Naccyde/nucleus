#include <nucleus/lib/string.h>

size_t strlen(const uint8_t *s)
{
	size_t len = 0;

	while (s[len])
		++len;

	return len;
}
