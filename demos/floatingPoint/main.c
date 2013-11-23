#include <ch.h>
#include <hal.h>
#include <chprintf.h>


/*led blinking*/
static WORKING_AREA (heartWrkArea, 64);
static msg_t heartBeat (void *arg)
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


static WORKING_AREA (floatingWrkArea, 512);
static msg_t floatingPoint (void *arg)
{
	for (float var = 1; var >= 0, var = var-0.0001;)
	{
		chprintf ((BaseSequentialStream *)&SD2, "%f \n\r", var);	
	}
}


int main (void)
{
	halInit();
	chSysInit();

	sdStart (&SD2, NULL);

	chThdCreateStatic (heartWrkArea, sizeof (heartWrkArea), NORMALPRIO, heartBeat, NULL);
	chThdCreateStatic (floatingWrkArea, sizeof (floatingWrkArea), NORMALPRIO, floatingPoint, NULL);
}