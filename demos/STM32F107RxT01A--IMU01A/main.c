/*
Demo with the MLAB module IMU01A
Module is connected to the second i2c bus
Data are printed out through the second serial bus
This demo reads and print out accelerometr and gyroscope axis and the temperature of the gyroscope chip

Created by Ondra Sestak 2013
*/

#include <ch.h>
#include <hal.h>
#include <IMU01A.h>
#include <chprintf.h>

/*i2c driver configuration*/
static const I2CConfig i2cCfg = {
    OPMODE_I2C,
    400000, /*400 kHz*/
    FAST_DUTY_CYCLE_2,
};

/*led blinking theard*/
static WORKING_AREA (heartWrkArea, 32);
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

/*main sensor reading and printing out theard*/
static WORKING_AREA (sensorsWrkArea, 256);
static msg_t sensorsRead (void*arg)
{
    float acc_x, acc_y, acc_z;
    float gyro_x, gyro_y, gyro_z;
    uint8_t temp;

	/*sensors initializing*/
    gyroInit (&I2CD2, IMU01A_GYRO);
    accInit (&I2CD2, IMU01A_ACC);
    chprintf ((BaseSequentialStream *)&SD2, "Configuration done\n\r");

    while (true)
    {
    	/*gyroscope and temperature reading*/
        gyroRead (&I2CD2, IMU01A_GYRO, &gyro_x, &gyro_y, &gyro_z);
        tempRead (&I2CD2, IMU01A_GYRO, &temp);
        /*accelerometer reading*/
        accRead (&I2CD2, IMU01A_ACC, &acc_x, &acc_y, &acc_z);

        /*printing out magnetometer values*/
        chprintf ((BaseSequentialStream *)&SD2, "%f gX    %f gY    %f gZ    ", gyro_x, gyro_y, gyro_z);      
        /*printing out accelerometer and temperature values*/
        chprintf ((BaseSequentialStream *)&SD2, "%f aX    %f aY    %f aZ    ", acc_x, acc_y, acc_z);
        chprintf ((BaseSequentialStream *)&SD2, "%d T\n\r", temp);     	
    }
}


int main (void)
{
	halInit();
	chSysInit();

	sdStart (&SD2, NULL);
    i2cStart (&I2CD2, &i2cCfg);

	chThdCreateStatic (heartWrkArea, sizeof (heartWrkArea), NORMALPRIO, heartBeat, NULL);
	chThdCreateStatic (sensorsWrkArea, sizeof (sensorsWrkArea), NORMALPRIO, sensorsRead, NULL);
}
