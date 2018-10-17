#include <nucleus/video/vga.h>

#include <nucleus/io/io.h>
#include <nucleus/lib/string.h>

#define VGA_MEMORY 0xb8000

/* Framebuffer ports */
#define FB_COMMAND_PORT	0x3D4
#define FB_DATA_PORT 	0xD5

/* Framebuffer commands */
#define FB_HIGH_BYTE_COMMAND 	14
#define FB_LOW_BYTE_COMMAND 	15

#define vga_entry(c, fg, bf) ((c) | (bg) << 8 | (fg) << 12)

static const size_t con_width = 80;
static const size_t con_height = 25;
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
	uint16_t pos = y * con_width + x;
 
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
	uint16_t i = y * con_width + x;
	vga_mem[i] = c;
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

	if (con_col >= con_width) {
		con_col = 0;
		++con_row;
	}

	if (con_row >= con_height) {
		vga_scroll();
		
		con_row = con_height-1;
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
	uint16_t from = con_width;

	for ( ; from < con_width * con_height; )
		vga_mem[to++] = vga_mem[from++];
	
	vga_clr_line(con_height - 1);
}

inline void vga_clr_line(uint8_t y)
{
	vga_clr_from_to(0, y, con_width, y, ' ', VGA_COLOR_BLACK,
		VGA_COLOR_WHITE);
}

void vga_clr(uint8_t v, enum vga_color fg, enum vga_color bg)
{
	vga_clr_from_to(0, 0, con_width, con_height, v, fg, bg);
}

void vga_clr_default(void)
{
	vga_clr_from_to(0, 0, con_width, con_height, ' ', VGA_COLOR_BLACK,
		VGA_COLOR_WHITE);
}

void vga_clr_from_to(uint8_t xfrom, uint8_t yfrom, uint8_t xto, uint8_t yto, uint8_t v, enum vga_color fg, enum vga_color bg)
{
	con_col = xfrom;
	con_row = yfrom;

	uint32_t from = yfrom * con_width + xfrom;
	uint32_t to = yto * con_width + xto;

	for (from; from < to; ++from)
		vga_mem[from] = vga_entry(v, fg, bg);
}

void vga_panic(void)
{
	disable_crsr();
	
	vga_clr_from_to(0, 0, con_width, 0, ' ', VGA_COLOR_WHITE,
		VGA_COLOR_RED);

	vga_write_str("                                  KERNEL PANIC!\n");
}
