#include <nucleus/debug.h>

#include <nucleus/io/serial.h>
#include <nucleus/io/io.h>
#include <nucleus/video/vga.h>

#define LOG_SERIAL_COM SERIAL_COM1

void log(const uint8_t *s)
{
	serial_write_str(LOG_SERIAL_COM, s);
	puts(s);
}

void panic(struct machine_state *state)
{
	vga_hide_cursor();
	
	vga_clr_from_to(0, 0, VGA_CON_WIDTH, 0, ' ', VGA_COLOR_WHITE,
		VGA_COLOR_RED);
	vga_write_str("                                  KERNEL PANIC!\n");

	vga_clr_from_to(0, 1, VGA_CON_WIDTH, VGA_CON_HEIGHT-1, ' ',
		VGA_COLOR_RED, VGA_COLOR_BLACK);
	vga_write_str("\nAn error happened\n");

	vga_clr_from_to(0, VGA_CON_HEIGHT-2, VGA_CON_WIDTH, VGA_CON_HEIGHT,
		' ', VGA_COLOR_WHITE, VGA_COLOR_RED);
	vga_write_str("Error code: 0x35\n");
}
