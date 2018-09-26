#ifndef _NUCLEUS_VIDEO_VGA_H
#define _NUCLEUS_VIDEO_VGA_H

#include "types.h"

void vga_init(void);
void vga_write_char_at(uint8_t c, uint8_t x, uint8_t y);
void vga_write_char(uint8_t c);
void vga_write(const uint8_t *d, size_t size);
void vga_write_str(const uint8_t *s);
void vga_scroll(void);
void vga_clr_line(uint8_t y);
void vga_clr(void);

#endif
