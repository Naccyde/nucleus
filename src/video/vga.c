#include "video/vga.h"

#include "io/io.h"
#include "lib/string.h"

#define VGA_MEMORY 0xb8000

/* Framebuffer ports */
#define FB_COMMAND_PORT	0x3D4
#define FB_DATA_PORT 	0xD5

/* Framebuffer commands */
#define FB_HIGH_BYTE_COMMAND 	14
#define FB_LOW_BYTE_COMMAND 	15

#define vga_entry(c) (uint16_t)(c) | (uint16_t)0x07 << 8;

enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE,
	VGA_COLOR_GREEN,
	VGA_COLOR_CYAN,
	VGA_COLOR_RED,
	VGA_COLOR_PURPLE,
	VGA_COLOR_BROWN,
	VGA_COLOR_GREY,
	VGA_COLOR_DARK_GREY,
	VGA_COLOR_LIGHT_BLUE,
	VGA_COLOR_LIGHT_GREEN,
	VGA_COLOR_LIGHT_CYAN,
	VGA_COLOR_LIGHT_RED,
	VGA_COLOR_LIGHT_PURPLE,
	VGA_COLOR_YELLOW,
	VGA_COLOR_WHITE
};

static const size_t con_width = 80;
static const size_t con_height = 25;
static uint16_t * const vga_mem = (uint16_t * const)VGA_MEMORY;
static uint8_t con_row = 0;
static uint8_t con_col = 0;

static inline void disable_crsr()
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, 0x20);
}

void vga_init(void)
{
	disable_crsr();
	vga_clr();
}

void vga_write_char_at(uint8_t c, uint8_t x, uint8_t y)
{
	uint16_t i = y * con_width + x;
	vga_mem[i] = vga_entry(c);
}

void vga_write_char(uint8_t c)
{
	switch (c) {
	case '\n':
		++con_row;
		con_col = 0;
		break;
	default:
		vga_write_char_at(c, con_col++, con_row);
		break;
	}

	if (con_col >= con_width) {
		con_col = 0;
		++con_row;
	}

	if (con_row >= con_height) {
		vga_scroll();
		
		con_row = con_height-1;
	}
}

void vga_write(const uint8_t *d, size_t size)
{
	for (size_t i = 0; i < size; ++i)
		vga_write_char(d[i]);
}

void vga_write_str(const uint8_t *s)
{
	vga_write(s, strlen(s));
}

void vga_scroll(void)
{
	uint16_t to = 0;
	uint16_t from = con_width;

	for ( ; from < con_width * con_height; )
		vga_mem[to++] = vga_mem[from++];
	
	vga_clr_line(con_height - 1);
}

inline void vga_clr_line(uint8_t y)
{
	for (size_t i = con_width * y; i < con_width * (y + 1); ++i)
		vga_mem[i] = vga_entry(' ');
}

void vga_clr(void)
{
	con_col = 0;
	con_row = 0;

	for (uint8_t i = 0; i < con_height; ++i)
		vga_clr_line(i);
}

/*
#define CON_WIDTH 80
#define CON_HEIGHT 25


static uint8_t x = 0;
static uint8_t y = 0;
static uint16_t con_theme = 0x07;

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
*/