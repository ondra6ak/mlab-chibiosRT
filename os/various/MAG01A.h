/*
Part of library for the MLAB module MAG01A.

Created by Ondra Sestak 2013
*/
#define MAG01A 0x1E
#define MAG01A_AXIS 0x03

void magInit(I2CDriver *i2c_drv, uint8_t addr);
void magRead (I2CDriver *i2c_drv, uint8_t addr, uint16_t *mag_x, uint16_t *mag_y, uint16_t *mag_z);