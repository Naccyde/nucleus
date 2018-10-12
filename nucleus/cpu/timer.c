#include <nucleus/cpu/timer.h>

#include <nucleus/debug.h>

#define PIT_FREQUENCY 	1193182
#define PIT_CHAN_0_PORT	0x40
#define PIT_CHAN_1_PORT	0x41
#define PIT_CHAN_2_PORT	0x42
#define PIT_CMD_PORT	0x43

#define PIT_CMD_BCD		0x1
#define PIT_CMD_MODE_INT_ON_TERM	0x0
#define PIT_CMD_MODE_HARD_RETR_ONE	0x2 // Hardware-retriggerable one-shot
#define PIT_CMD_MODE_RATE_GEN		0x4 // Rate generator
#define PIT_CMD_MODE_SQUARE_WAVE_GEN	0x6 // Square wave generator
#define PIT_CMD_MODE_SOFT_TR_STROBE	0x8 // Software trigerred strobes
#define PIT_CMD_MODE_HARD_TR_STROBE	0xa // Hardware triggered strobes
#define PIT_CMD_ACCESS_LOW		0x10
#define PIT_CMD_ACCESS_HIGH		0x20
#define PIT_CMD_ACCESS_LOWHIGH		0x30
#define PIT_CMD_CHAN0			0x0
#define PIT_CMD_CHAN1			0x40
#define PIT_CMD_CHAN2			0x80
#define PIT_CMD_READBACK		0xc0

void timer_init(void)
{

}

void timer_handler(struct int_machine_state *state)
{
	log("TIMER\n");
}
