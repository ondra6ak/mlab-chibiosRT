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


static WORKING_AREA (magDemoWrkArea, 256);
static msg_t magDemo (void*arg)
{
    magInit(&I2CD2, MAG01A);
    while (true)
    {
        int16_t x, y, z;
        magRead(&I2CD2, MAG01A, &x, &y, &z);
        /*tisknuti namerenych hodnot*/
        chprintf ((BaseSequentialStream *)&SD2, "%d X     ", x);
        chprintf ((BaseSequentialStream *)&SD2, "%d Y     ", y);
        chprintf ((BaseSequentialStream *)&SD2, "%d Z     ", z);
        chprintf ((BaseSequentialStream *)&SD2, "\n\r");     	
    }
}


int main (void)
{
	halInit();
	chSysInit();

	sdStart (&SD2, NULL);
    i2cStart (&I2CD2, &i2cCfg);


	chThdCreateStatic (heartWrkArea, sizeof (heartWrkArea), NORMALPRIO, heartBeat, NULL);
	chThdCreateStatic (magDemoWrkArea, sizeof (magDemoWrkArea), NORMALPRIO, magDemo, NULL);
}