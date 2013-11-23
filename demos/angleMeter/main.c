/*
demo s modulem MAG01A 
modul I2C2 
seriovka SD2
*/

#include <ch.h>
#include <hal.h>
#include <MAG01A.h>
#include <IMU01A.h>
#include <chprintf.h>


static const I2CConfig i2cCfg = {
	OPMODE_I2C,
	400000, /*400 kHz*/
	FAST_DUTY_CYCLE_2,
};

/*led blinking*/
static WORKING_AREA (heartWrkArea, 32);
static msg_t heartBeat (void*Arg)
{
	chprintf ((BaseChannel *)&SD2, "Hello world!\n\r");

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


static WORKING_AREA (sensorsReadWrkArea, 256);
static msg_t sensorsRead (void*arg)
{
	int16_t magX, magY, magZ;
    int16_t accX, accY, accZ;

    magInit (&I2CD2, MAG01A);
    accInit (&I2CD2, IMU01A_ACC);
    while (true)
    {
        magRead (&I2CD2, MAG01A, &magX, &magY, &magZ);
        accRead (&I2CD2, IMU01A_ACC, &accX, &accY, &accZ);
        /*tisknuti namerenych hodnot*/
        chprintf ((BaseChannel *)&SD2, "%d magX     ", magX);
        chprintf ((BaseChannel *)&SD2, "%d magY     ", magY);
        chprintf ((BaseChannel *)&SD2, "%d magZ     ", magZ);
        chprintf ((BaseChannel *)&SD2, "%d accX     ", accX);
        chprintf ((BaseChannel *)&SD2, "%d accY     ", accY);
        chprintf ((BaseChannel *)&SD2, "%d accZ     ", accZ);
        chprintf ((BaseChannel *)&SD2, "\n\r");     
        chThdSleepMilliseconds (5);	
    }
}


int main (void)
{
	halInit();
	chSysInit();

	sdStart (&SD2, NULL);
    i2cStart (&I2CD2, &i2cCfg);


	chThdCreateStatic (heartWrkArea, sizeof (heartWrkArea), NORMALPRIO, heartBeat, NULL);
	chThdCreateStatic (sensorsReadWrkArea, sizeof (sensorsReadWrkArea), NORMALPRIO, sensorsRead, NULL);
}