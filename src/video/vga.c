#include "video/vga.h"

#include "io/io.h"

#define CON_WIDTH 80
#define CON_HEIGHT 25
#define VGA_MEMORY 0xb8000

static uint8_t x = 0;
static uint8_t y = 0;
static uint16_t con_theme = 0x07;

enum VGA_COLOR {
	BLACK = 0,
	BLUE,
	GREEN,
	CYAN,
	RED,
	PURPLE,
	BROWN,
	GREY,
	DARK_GREY,
	LIGHT_BLUE,
	LIGHT_GREEN,
	LIGHT_CYAN,
	LIGHT_RED,
	LIGHT_PURPLE,
	YELLOW,
	WHITE
};

static void disable_crsr()
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, 0x20);
}

void con_init(void)
{
	disable_crsr();
	con_clr();
}

void con_clr(void)
{
	uint8_t *v = (uint8_t *)VGA_MEMORY;

	for (uint16_t i = 0; i < CON_WIDTH * CON_HEIGHT * 2; i += 2) {
		v[i] = 0;
		v[i+1] = con_theme;
	}
}

static void con_scroll()
{
	uint8_t *v = (uint8_t *)VGA_MEMORY;
	uint16_t lidx = 0;
	uint16_t uidx = CON_WIDTH * 2;

	for (uint8_t i = 0; i < (CON_HEIGHT - 1) * CON_WIDTH; ++i) {
		v[lidx] = v[uidx];
	}
}

void print(const int8_t *s)
{
	uint8_t *v = (uint8_t *)VGA_MEMORY;

	for ( ; *s != '\0'; ++s) {
		int8_t c = *s;
		uint16_t i = y * CON_WIDTH * 2 + x * 2;

		switch (c) {
		case '\n':
			++y;
			x = 0;
			break;
		default:
			v[i] = c;
			++x;
			break;
		}

		if (CON_WIDTH == x) {
			x = 0;
			++y;
		}

		if (CON_HEIGHT < y) {
			con_scroll();
			--y;
		}
	}
}
