#include <nucleus/video/vga.h>

#include <nucleus/io/io.h>
#include <nucleus/lib/string.h>

/*
 * VGA memory starts at 0xc00b8000 as kernel is loaded at virtual address
 * 0xc0000000.
 */
#define VGA_MEMORY 0xc00b8000

/* Framebuffer ports */
#define FB_COMMAND_PORT	0x3D4
#define FB_DATA_PORT 	0xD5

/* Framebuffer commands */
#define FB_HIGH_BYTE_COMMAND 	14
#define FB_LOW_BYTE_COMMAND 	15

#define vga_entry(c, fg, bf) ((c) | (bg) << 8 | (fg) << 12)

static uint16_t * const vga_mem = (uint16_t * const)VGA_MEMORY;
static uint8_t con_row = 0;
static uint8_t con_col = 0;

static inline void disable_crsr(void)
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, 0x20);
}

static inline void enable_crsr(void)
{
	// TODO: write this function
}

static inline void update_crsr(uint8_t x, uint8_t y)
{
	// TODO: explain a bit more the content of this function
	uint16_t pos = y * VGA_CON_WIDTH + x;
 
	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

void vga_init(void)
{
	vga_clr_default();
}

void vga_write_char_at(uint8_t c, uint8_t x, uint8_t y)
{
	uint16_t i = y * VGA_CON_WIDTH + x;
	vga_mem[i] = c | (vga_mem[i] & 0xff00);
}

void vga_write_char(uint8_t c)
{
	switch (c) {
	case '\n':
		++con_row;
		con_col = 0;
		break;
	case '\b':
		// TODO: handle this case
		break;
	case '\t':
		// TODO: handle this case
		vga_write_char_at(' ', con_col++, con_row);
		break;
	default:
		vga_write_char_at(c, con_col++, con_row);
		break;
	}

	if (con_col >= VGA_CON_WIDTH) {
		con_col = 0;
		++con_row;
	}

	if (con_row >= VGA_CON_HEIGHT) {
		vga_scroll();
		
		con_row = VGA_CON_HEIGHT-1;
	}

	update_crsr(con_col, con_row);
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
	uint16_t from = VGA_CON_WIDTH;

	for ( ; from < VGA_CON_WIDTH * VGA_CON_HEIGHT; )
		vga_mem[to++] = vga_mem[from++];
	
	vga_clr_line(VGA_CON_HEIGHT - 1);
}

void vga_hide_cursor(void)
{
	disable_crsr();
}

inline void vga_clr_line(uint8_t y)
{
	vga_clr_from_to(0, y, VGA_CON_WIDTH, y, ' ', VGA_COLOR_BLACK,
		VGA_COLOR_WHITE);
}

void vga_clr(uint8_t v, enum vga_color fg, enum vga_color bg)
{
	vga_clr_from_to(0, 0, VGA_CON_WIDTH, VGA_CON_HEIGHT, v, fg, bg);
}

void vga_clr_default(void)
{
	vga_clr_from_to(0, 0, VGA_CON_WIDTH, VGA_CON_HEIGHT, ' ', VGA_COLOR_BLACK,
		VGA_COLOR_WHITE);
}

void vga_clr_from_to(uint8_t xfrom, uint8_t yfrom, uint8_t xto, uint8_t yto, uint8_t v, enum vga_color fg, enum vga_color bg)
{
	con_col = xfrom;
	con_row = yfrom;

	uint32_t from = yfrom * VGA_CON_WIDTH + xfrom;
	uint32_t to = yto * VGA_CON_WIDTH + xto;

	for ( ; from < to; ++from)
		vga_mem[from] = vga_entry(v, fg, bg);
}
