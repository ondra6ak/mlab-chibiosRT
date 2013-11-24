/*
Library for the MLAB module MAG01A with Honeywell's HMC5883 chip. This library let you configure the magnetometer to a
fastest and direct data streaming and read out calibrated values.

Created by Ondra Sestak 2013
*/

#include <ch.h>
#include <hal.h>
#include <chprintf.h>
#include <MAG01A.h>
#include <i2cGetErr.h>


void magInit(I2CDriver *i2c_drv, uint8_t addr)
{
    uint8_t tx_data[8]; 
    msg_t msg;

    tx_data[0] = 0x00; /*register B*/
    tx_data[1] = 0xf8; 
    i2cAcquireBus (i2c_drv);
	msg = i2cMasterTransmitTimeout (i2c_drv, addr, tx_data, 2, 0, 0, MS2ST(4));
	i2cReleaseBus (i2c_drv);
    if (msg != RDY_OK) i2cGetErr(i2c_drv, &SD_DRV);

    tx_data[0] = 0x01; /*register B*/
    tx_data[1] = 0x20;
    i2cAcquireBus (i2c_drv);
	msg = i2cMasterTransmitTimeout (i2c_drv, addr, tx_data, 2, 0, 0, MS2ST(4));
	i2cReleaseBus (i2c_drv);
    if (msg != RDY_OK) i2cGetErr(i2c_drv, &SD_DRV);

    tx_data[0] = 0x02; /*register MODE*/
    tx_data[1] = 0x00;
    i2cAcquireBus (i2c_drv);
	msg = i2cMasterTransmitTimeout (i2c_drv, addr, tx_data, 2, 0, 0, MS2ST(4));
	i2cReleaseBus (i2c_drv);
    if (msg != RDY_OK) i2cGetErr(i2c_drv, &SD_DRV);

}

/*axis reading*/
void magRead (I2CDriver *i2c_drv, uint8_t addr, uint16_t *mag_x, uint16_t *mag_y, uint16_t *mag_z)
{
    uint8_t tx_data[8]; 
    uint8_t rx_data[6];
    msg_t msg;

   	tx_data[0] = MAG01A_AXIS;
   	i2cAcquireBus (i2c_drv);
    msg = i2cMasterTransmitTimeout (i2c_drv, addr, tx_data, 1, rx_data, 6, MS2ST(4));
    i2cReleaseBus (i2c_drv);
    if (msg != RDY_OK) i2cGetErr(i2c_drv, &SD_DRV);

    *mag_x = (rx_data[0] << 8) | rx_data[1];
    *mag_y = (rx_data[4] << 8) | rx_data[5];
    *mag_z = (rx_data[2] << 8) | rx_data[3];
}