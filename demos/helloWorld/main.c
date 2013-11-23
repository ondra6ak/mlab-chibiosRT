#include <ch.h>
#include <hal.h>
#include <chprintf.h>


/*led blinking*/
static WORKING_AREA (heartWrkArea, 64);
static msg_t heartBeat (void*Arg)
{
	chprintf ((BaseSequentialStream *)&SD2, "\n\rHello world!\n\r");

	while (true)
	{
		palSetPad (GPIOB, 8);
		palClearPad (GPIOB, 7);
		chThdSleepMilliseconds (250);
		palClearPad (GPIOB, 8);
		palSetPad (GPIOB, 7);
		chThdSleepMilliseconds (250);
	}
}


static WORKING_AREA (commWrkArea, 128);
static msg_t communication (void*Arg)
{
	int c;

    chprintf ((BaseSequentialStream *)&SD2, ">");

	while (true)
	{
		c = sdGet (&SD2);

		if (c == 13) chprintf ((BaseSequentialStream *)&SD2, "\n\r>");
		else chprintf ((BaseSequentialStream *)&SD2, "%c", c);
	}
}


int main (void)
{
	halInit();
	chSysInit();

	sdStart (&SD2, NULL);

	chThdCreateStatic (heartWrkArea, sizeof (heartWrkArea), NORMALPRIO, heartBeat, NULL);
	chThdCreateStatic (commWrkArea, sizeof (commWrkArea), NORMALPRIO, communication, NULL);
}
