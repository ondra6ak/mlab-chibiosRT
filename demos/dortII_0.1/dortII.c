#include <ch.h>
#include <hal.h>
#include "chprintf.h"
#include "dortII.h"


void printf (const char *str, int *var)
{
	if (dip1 == 0)
	{
		if (var == 0)
		{
			chprintf ((BaseChannel *)&SD2, "%s", str);
		}
		else
		{
			chprintf ((BaseChannel *)&SD2, "%s", str, var);
		}
	}
}

move (uint8_t dir, uint8_t usr_spd)
{
	int spd = 20000/255*usr_spd;
	chprintf  ((BaseChannel *)&SD2, "%d \n\r", spd);
	if (dir == FWD)
	{
		pwmDisableChannel (&PWMD3, MOTOR_L_REV);
		pwmDisableChannel (&PWMD3, MOTOR_R_REV);
		pwmEnableChannel (&PWMD3, MOTOR_L_FWD, spd);
		pwmEnableChannel (&PWMD3, MOTOR_R_FWD, spd);
	}
	else if (dir == REV)
	{
		pwmDisableChannel (&PWMD3, MOTOR_L_FWD);
		pwmDisableChannel (&PWMD3, MOTOR_R_FWD);
		pwmEnableChannel (&PWMD3, MOTOR_L_REV, spd);
		pwmEnableChannel (&PWMD3, MOTOR_R_REV, spd);
	}
	else if (dir == LEFT)
	{
		pwmDisableChannel (&PWMD3, MOTOR_L_FWD);
		pwmDisableChannel (&PWMD3, MOTOR_R_REV);
		pwmEnableChannel (&PWMD3, MOTOR_L_REV, spd);
		pwmEnableChannel (&PWMD3, MOTOR_R_FWD, spd);
	}
	else if (dir == RIGHT)
	{
		pwmDisableChannel (&PWMD3, MOTOR_L_REV);
		pwmDisableChannel (&PWMD3, MOTOR_R_FWD);
		pwmEnableChannel (&PWMD3, MOTOR_L_FWD, spd);
		pwmEnableChannel (&PWMD3, MOTOR_R_REV, spd);
	}
}