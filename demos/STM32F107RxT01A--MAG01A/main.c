/*
demo s modulem MAG01A 
modul I2C2 
seriovka SD2
*/

#include <ch.h>
#include <hal.h>
#include <MAG01A.h>
#include <chprintf.h>


static const I2CConfig i2cCfg = {
	OPMODE_I2C,
	400000, /*400 kHz*/
	FAST_DUTY_CYCLE_2,
};

/*led blinking theard*/
static WORKING_AREA (heartWrkArea, 64);
static msg_t heartBeat (void*arg)
{
	chprintf ((BaseSequentialStream *)&SD2, "\n\rHello world!\n\r");

    palSetPad (GPIOB, LED1);
    palClearPad (GPIOB, LED2);

	while (true)
	{
		palTogglePad (GPIOB, LED1);
		palTogglePad (GPIOB, LED2);
		chThdSleepMilliseconds (250);
	}
}


static WORKING_AREA (magDemoWrkArea, 512);
static msg_t magDemo (void*arg)
{
	uint16_t x, y, z;

    /*magnetometer configuration*/
    magInit(&I2CD2, MAG01A);
    chprintf ((BaseSequentialStream *)&SD2, "Configuration done\n\r");

    while (true)
    {
        /*magnetometer reading*/
        magRead(&I2CD2, MAG01A, &x, &y, &z);
        chprintf ((BaseSequentialStream *)&SD2, "%d X     %d Y     %d Z\n\r", x, y, z);    	
    }
}


int main (void)
{
	halInit();
	chSysInit();

    palSetPadMode(GPIOB, 10, PAL_MODE_STM32_ALTERNATE_OPENDRAIN);
    palSetPadMode(GPIOB, 11, PAL_MODE_STM32_ALTERNATE_OPENDRAIN);
    chThdSleepMilliseconds(100);  /* Just to be safe. */

	sdStart (&SD2, NULL);
    i2cStart (&I2CD2, &i2cCfg);


	chThdCreateStatic (heartWrkArea, sizeof (heartWrkArea), NORMALPRIO, heartBeat, NULL);
	chThdCreateStatic (magDemoWrkArea, sizeof (magDemoWrkArea), NORMALPRIO, magDemo, NULL);
}