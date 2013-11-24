/*
Part of library for the MLAB module MAG01A.

Created by Ondra Sestak 2013
*/

#define MAG01A 0x1E
#define MAG01A_AXIS 0x03

void magInit(I2CDriver *i2c_drv, uint8_t addr);
void magRead (I2CDriver *i2c_drv, uint8_t addr, float *mag_x, float *mag_y, float *mag_z);