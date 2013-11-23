/*
Part of i2c troubleshooting library

Created by Ondra Sestak 2013
*/
#ifndef _i2cGetErr_H_
#define _i2cGetErr_H_
#endif

#define SD_DRV SD2 /*serial bus*/
#define SYS_HALT TRUE /*if errorr halt the system*/

void i2cGetErr(I2CDriver *i2c_drv, SerialDriver *sd_drv);