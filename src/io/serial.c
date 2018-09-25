#include "io/serial.h"

#include "io/io.h"

/*
 * All the serial I/O port are calculated the same way for all serial ports.
 * This is because their ports are in the same order, but with a different
 * base.
 */
#define SERIAL_COM1_BASE	0x3f8
#define SERIAL_COM2_BASE	0x2f8
#define SERIAL_COM3_BASE	0x3e8
#define SERIAL_COM4_BASE	0x2e8

#define SERIAL_DATA_PORT(base)		(base)
#define SERIAL_FIFO_CMD_PORT(base)	((base) + 2)
#define SERIAL_LINE_CMD_PORT(base)	((base) + 3)
#define SERIAL_MODEM_CMD_PORT(base)	((base) + 4)
#define SERIAL_LINE_STATUS_PORT(base)	((base) + 5)

/*
 * SERIAL_LINE_ENABLE_DLAB:
 * Used to tell the serial port to expect first the highest 8 bits on the data
 * port, then the lowest 8 bits.
 */
#define SERIAL_LINE_ENABLE_DLAB		0x80

void serial_configure_baud_rate(uint16_t com, uint16_t divisor)
{
	outb(SERIAL_LINE_CMD_PORT(com), SERIAL_LINE_ENABLE_DLAB);
	outb(SERIAL_DATA_PORT(com), (divisor >> 8) & 0x00ff);
	outb(SERIAL_DATA_PORT(com), divisor & 0x00ff);
}

void serial_configure_line(uint16_t com)
{
	/*
	 * Configure serial line with default value 0x03:
	 * Bit:     | 7 | 6 | 5 4 3 | 2 | 1 0 |
         * Content: | d | b | prty  | s | dl  |
         * Value:   | 0 | 0 | 0 0 0 | 0 | 1 1 |
         */
	outb(SERIAL_LINE_CMD_PORT(com), 0x03);
}

void serial_configure_buffers(uint16_t com, uint8_t conf)
{

}

void serial_configure_modem(uint16_t com, uint8_t conf)
{

}
