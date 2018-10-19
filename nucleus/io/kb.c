#include <nucleus/io/kb.h>

#include <nucleus/io/io.h>
#include <nucleus/lib/stdlib.h>

uint8_t kbdus[128] =
{
	0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	'9', '0',
	'-', '=', '\b',	'\t',
	'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',
	'[', ']', '\n', 0,
	'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
	'\'', '`',  0, '\\',
	'z', 'x', 'c', 'v', 'b', 'n', 'm',
	',', '.', '/', 0, '*',
	0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '-', 0, 0, 0,
	'+', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

void keyboard_handler(struct machine_state *state)
{
	UNUSED(state);

	uint8_t scancode;

	/* Read from the keyboard's data buffer */
	scancode = inb(0x60);

	/* If the top bit of the byte we read from the keyboard is
	*  set, that means that a key has just been released */
	if (scancode & 0x80) {
		/*
		 * Handle shift, alt and other control keys
		 */
	} else {
		putch(kbdus[scancode]);
	}
}
