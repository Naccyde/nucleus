#ifndef _NUCLEUS_VIDEO_VGA_H
#define _NUCLEUS_VIDEO_VGA_H

#include <nucleus/types.h>

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

void vga_init(void);
void vga_write_char_at(uint8_t c, uint8_t x, uint8_t y);
void vga_write_char(uint8_t c);
void vga_write(const uint8_t *d, size_t size);
void vga_write_str(const uint8_t *s);
void vga_scroll(void);

void vga_clr_line(uint8_t y);
void vga_clr(uint8_t v, enum vga_color fg, enum vga_color bg);
void vga_clr_default(void);
void vga_clr_from_to(uint8_t xfrom, uint8_t yfrom, uint8_t xto, uint8_t yto, uint8_t v, enum vga_color fg, enum vga_color bg);

void vga_panic(void);

#endif
