#include <nucleus/lib/string.h>

size_t strlen(const uint8_t *s)
{
	size_t len = 0;

	while (s[len])
		++len;

	return len;
}

void strrev(uint8_t *s)
{
	uint8_t c;

	for (size_t i = 0, j = strlen(s) - 1; i < j; ++i, --j) {
		c = s[i];
		s[i] = s[j];
		s[j] = c; 
	}
}

bool itoa(int32_t value, uint8_t *s, size_t len)
{
	size_t i = 0;
	bool ret = true;
	bool negative = false;
	
	if (2 > len) {
		ret = false;
		goto end;
	}

	if (value < 0) {
		negative = true;
		value = -value;
	}

	do {
		s[i++] = value % 10 + '0';
		--len;
	} while ((value /= 10) > 0 && len > 1);

	if (negative) {
		s[i++] = '-';
		--len;
	}
	
	if (0 == len) {
		ret = false;
		goto end;
	}

	s[i++] = '\0';

	strrev(s);

end:
	return ret;
}
