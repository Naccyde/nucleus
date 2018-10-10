#include <nucleus/io/serial.h>

#include <nucleus/io/io.h>
#include <nucleus/lib/string.h>
#include <nucleus/video/vga.h>

/*
 * TODO: Handle Line Status Register errors
 * TODO: Manage Modem Status Register
 */

/*
 * Serial line registers addresses
 */
#define SERIAL_DATA_PORT(base)		(base)
#define SERIAL_INTERRUPT_PORT(base)	((base) + 1)
#define SERIAL_FIFO_CMD_PORT(base)	((base) + 2)
#define SERIAL_LINE_CMD_PORT(base)	((base) + 3)
#define SERIAL_MODEM_CMD_PORT(base)	((base) + 4)
#define SERIAL_LINE_STATUS_PORT(base)	((base) + 5)
#define SERIAL_MODEM_STATUS_PORT(base)	((base) + 6)
#define SERIAL_SCRATCH_CMD_PORT(base)	((base) + 7)

/*
 * Serial line register configuration
 */
#define SERIAL_LINE_DATA_5		0x00
#define SERIAL_LINE_DATA_6		0x01
#define SERIAL_LINE_DATA_7		0x02
#define SERIAL_LINE_DATA_8		0x03
#define SERIAL_LINE_STOP_1		0x00
#define SERIAL_LINE_STOP_2		0x04
#define SERIAL_LINE_PARITY_NONE		0x00
#define SERIAL_LINE_PARITY_ODD		0x08
#define SERIAL_LINE_PARITY_EVEN		0x18
#define SERIAL_LINE_PARITY_MARK		0x28
#define SERIAL_LINE_PARITY_SPACE	0x38
#define SERIAL_LINE_BREAK_CTRL		0x40
#define SERIAL_LINE_DLAB		0x80 

/*
 * Serial buffer register configuration
 */
#define SERIAL_BUFFER_FIFO		0x01
#define SERIAL_BUFFER_CLR_RX		0x02
#define SERIAL_BUFFER_CLR_TX		0x04
#define SERIAL_BUFFER_DMA		0x08
#define SERIAL_BUFFER_64B		0x20
#define SERIAL_BUFFER_LEN_1		0x00
#define SERIAL_BUFFER_LEN_4		0x40
#define SERIAL_BUFFER_LEN_8		0x80
#define SERIAL_BUFFER_LEN_14		0xc0

/*
 * Serial modem register configuration
 */
#define SERIAL_MODEM_DTR		0x01	// Data Terminal Ready
#define SERIAL_MODEM_RTS		0x02	// Ready To Transmit
#define SERIAL_MODEM_AUX_OUT_1		0x04
#define SERIAL_MODEM_AUX_OUT_2		0x08
#define SERIAL_MODEM_LOOPBACK		0x10
#define SERIAL_MODEM_AUTOFLOW_CTRL	0x20

/*
 * Serial line status register
 */
#define SERIAL_LINE_STATUS_DATA_RDY	0x01
#define SERIAL_LINE_STATUS_OVERRUN_ERR	0x02
#define SERIAL_LINE_STATUS_PARITY_ERR	0x04
#define SERIAL_LINE_STATUS_FRAMING_ERR	0x08
#define SERIAL_LINE_STATUS_BRK_INT	0x10
#define SERIAL_LINE_STATUS_EMPTY_TX	0x20
#define SERIAL_LINE_STATUS_EMPTY_RX	0x40
#define SERIAL_LINE_STATUS_FIFO_ERR	0x80

static void serial_configure_line(uint16_t com, uint8_t conf)
{
	outb(SERIAL_LINE_CMD_PORT(com), conf);
}

static void serial_configure_baud_rate(uint16_t com, uint16_t divisor)
{
	// Set DLAB bit
	serial_configure_line(com, SERIAL_LINE_DLAB);

	// Write divisor in proper register
	outb(SERIAL_DATA_PORT(com), (divisor >> 8) & 0x00ff);
	outb(SERIAL_INTERRUPT_PORT(com), divisor & 0x00ff);

	// Clear DLAB bit
	serial_configure_line(com, 0);
}

static void serial_configure_buffers(uint16_t com, uint8_t conf)
{
	outb(SERIAL_FIFO_CMD_PORT(com), conf);
}

static void serial_configure_modem(uint16_t com, uint8_t conf)
{
	outb(SERIAL_MODEM_CMD_PORT(com), conf);
}

static bool serial_is_tx_empty(uint16_t com)
{
	return inb(SERIAL_LINE_STATUS_PORT(com)) & SERIAL_LINE_STATUS_EMPTY_TX;
}

static void serial_init(uint16_t com)
{
	/*
	 * All serial ports are initialized the same way:
	 * Baud rate divisor: 2
	 * Line: 8 bits data and one stop bit
	 * Buffer: 14 bytes long, FIFO and RX/TX cleared
	 * Modem: DTR & RTS
	 */

	serial_configure_baud_rate(com, 2);

	serial_configure_line(com,
		SERIAL_LINE_DATA_8 |
		SERIAL_LINE_STOP_1);

	serial_configure_buffers(com,
		SERIAL_BUFFER_FIFO | 
		SERIAL_BUFFER_CLR_RX | 
		SERIAL_BUFFER_CLR_TX | 
		SERIAL_BUFFER_LEN_14);

	serial_configure_modem(com,
		SERIAL_MODEM_DTR |
		SERIAL_MODEM_RTS);
}

void serial_init_all(void)
{
	serial_init(SERIAL_COM1);
	serial_init(SERIAL_COM2);
	serial_init(SERIAL_COM3);
	serial_init(SERIAL_COM4);
}

void serial_write(uint16_t com, const uint8_t *d, size_t len)
{
	// Currently, all serial port have 14 bytes buffers
	uint8_t fifo_size = 14;
	size_t remaining_len = len;

	// Fill all the serial buffer before checking serial port emptyness
	while (remaining_len) {
		uint8_t send_len = fifo_size;

		while (! serial_is_tx_empty(com));

		if (remaining_len <= fifo_size)
			send_len = remaining_len;

		for (uint8_t i = 0; i < send_len; ++i)
			outb(com, *d++);
		
		remaining_len -= send_len;
	}
}

void serial_write_str(uint16_t com, const uint8_t *s)
{
	serial_write(com, s, strlen(s));
}
