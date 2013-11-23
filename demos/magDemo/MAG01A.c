#include <ch.h>
#include <hal.h>
#include <chprintf.h>

#include <MAG01A.h>


void magInit(I2CDriver *i2c_drv, uint8_t addr)
{
    uint8_t tx_data[8]; 
    msg_t msg;

	/*configuration of the register A*/
    tx_data[0] = 0x00;
    tx_data[1] = 0xf8; 
    i2cAcquireBus (i2c_drv);
	msg = i2cMasterTransmitTimeout (i2c_drv, addr, tx_data, 2, 0, 0, MS2ST(4));
	i2cReleaseBus (i2c_drv);
    chThdSleepMilliseconds (5);
    if (msg != RDY_OK) i2cGetErr(i2c_drv);

    /*configurace registru B*/
    tx_data[0] = 0x01;
    tx_data[1] = 0x20;
    i2cAcquireBus (i2c_drv);
	msg = i2cMasterTransmitTimeout (i2c_drv, addr, tx_data, 2, 0, 0, MS2ST(4));
	i2cReleaseBus (i2c_drv);
    chThdSleepMilliseconds (5);
    if (msg != RDY_OK) i2cGetErr(i2c_drv);

    
    /*configurace modoveho registru*/
    tx_data[0] = 0x02;
    tx_data[1] = 0x00;
    i2cAcquireBus (i2c_drv);
	msg = i2cMasterTransmitTimeout (i2c_drv, addr, tx_data, 2, 0, 0, MS2ST(4));
	i2cReleaseBus (i2c_drv);
    chThdSleepMilliseconds (5);
    if (msg != RDY_OK) i2cGetErr(i2c_drv);

}


void magRead (I2CDriver *i2c_drv, uint8_t addr, int16_t *mag_x, int16_t *mag_y, int16_t *mag_z)
{
    uint8_t tx_data[8]; 
    uint8_t rx_data[6];
    msg_t msg;

   	tx_data[0] = MAG01A_AXIS;
   	i2cAcquireBus (i2c_drv);
    msg = i2cMasterTransmitTimeout (i2c_drv, addr, tx_data, 1, rx_data, 6, MS2ST(4));
    i2cReleaseBus (i2c_drv);
    if (msg != RDY_OK) i2cGetErr(i2c_drv);
      
    /*ulozeni namerenych hodnot do promenych*/
    *mag_x = (rx_data[0] << 8) | rx_data[1];
    *mag_y = (rx_data[2] << 8) | rx_data[3];
    *mag_y = (rx_data[4] << 8) | rx_data[5];
}