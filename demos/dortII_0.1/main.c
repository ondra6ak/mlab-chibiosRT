/* verze 0.2
ovladani a analogovy vstup.
2.10.2013 
*/

#include <ch.h>
#include <hal.h>
#include "dortII.h"


/*led blinking*/
static WORKING_AREA (heartWrkArea, 32);
static msg_t heartBeat (void*Arg)
{
	palSetPad (GPIOB, 8);
	palClearPad (GPIOB, 7);
	printf ("\n\rHello world!\n\r");

	while (true)
	{
    	palTogglePad (GPIOB, 8);
		palTogglePad (GPIOB, 7);
		chThdSleepMilliseconds (250);
	}
}


static WORKING_AREA (sensorWrkArea, 512);
static msg_t sensorRead (void*Arg)
{
	if (dip2 == 1)
	{
		while (true)
		{
    		adcStartConversion (&ADCD1, &adcGrpCfg, irSamples, ADC_BUF_DEPTH);
    		chprintf ((BaseChannel *)&SD2, "adc = \n\r", irSamples);
		}
	}

	int i = 255;
	while (i >= 0)
	{
		chprintf((BaseChannel *)&SD2, "%d  ", i);
		move (FWD, i);
		chThdSleepMilliseconds (100);
		--i;
	}

	i = 0;
	while (i >= 0)
	{
		chprintf((BaseChannel *)&SD2, "%d  ", i);
		move (LEFT, i);
		chThdSleepMilliseconds (100);
		--i;
	}

	i = 0;
	while (i >= 0)
	{
		chprintf((BaseChannel *)&SD2, "%d  ", i);
		move (RIGHT, i);
		chThdSleepMilliseconds (100);
		--i;
	}

	i = 0;
	while (i >= 0)
	{
		chprintf((BaseChannel *)&SD2, "%d  ", i);
		move (REV, i);
		chThdSleepMilliseconds (100);
		--i;
	}
}


int main (void)
{
	halInit();
	chSysInit();

	sdStart (&SD2, NULL);
	pwmStart (&PWMD3, &pwmCfg);
	adcStart (&ADCD1, &adcGrpCfg);

	palSetPadMode (GPIOA, 6, PAL_MODE_STM32_ALTERNATE_PUSHPULL);
	palSetPadMode (GPIOA, 7, PAL_MODE_STM32_ALTERNATE_PUSHPULL);
	palSetPadMode (GPIOB, 0, PAL_MODE_STM32_ALTERNATE_PUSHPULL);
	palSetPadMode (GPIOB, 1, PAL_MODE_STM32_ALTERNATE_PUSHPULL);
	palSetPadMode (GPIOC, 2, PAL_MODE_INPUT_ANALOG);

	chThdCreateStatic (heartWrkArea, sizeof (heartWrkArea), NORMALPRIO, heartBeat, NULL);
	chThdCreateStatic (sensorWrkArea, sizeof (sensorWrkArea), NORMALPRIO, sensorRead, NULL);
}
