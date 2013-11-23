#include <ch.h>
#include <hal.h>
#include <chprintf.h>

#include <MAG01A.h>


void magInit(I2CDriver *i2cDrv, uint8_t addr)
{
    uint8_t txData[8]; 
    msg_t msg;

	/*configurace registru A*/
    txData[0] = 0x00;
    txData[1] = 0xf8; 
    i2cAcquireBus (i2cDrv);
	msg = i2cMasterTransmitTimeout (i2cDrv, addr, txData, 2, 0, 0, MS2ST(4));
	i2cReleaseBus (i2cDrv, &SD_DRV);
    if (msg != RDY_OK) i2cGetErr(i2cDrv);

    /*configurace registru B*/
    txData[0] = 0x01;
    txData[1] = 0x20;
    i2cAcquireBus (i2cDrv);
	msg = i2cMasterTransmitTimeout (i2cDrv, addr, txData, 2, 0, 0, MS2ST(4));
	i2cReleaseBus (i2cDrv);
    if (msg != RDY_OK) i2cGetErr(i2cDrv, &SD_DRV);

    
    /*configurace modoveho registru*/
    txData[0] = 0x02;
    txData[1] = 0x00;
    i2cAcquireBus (i2cDrv);
	msg = i2cMasterTransmitTimeout (i2cDrv, addr, txData, 2, 0, 0, MS2ST(4));
	i2cReleaseBus (i2cDrv);
    if (msg != RDY_OK) i2cGetErr(i2cDrv, &SD_DRV);

}


void magRead (I2CDriver *i2cDrv, uint8_t addr, int16_t *magX, int16_t *magY, int16_t *magZ)
{
    uint8_t txData[8]; 
    uint8_t rxData[6];
    msg_t msg;

   	txData[0] = MAG01A_AXIS;
   	i2cAcquireBus (i2cDrv);
    msg = i2cMasterTransmitTimeout (i2cDrv, addr, txData, 1, rxData, 6, MS2ST(4));
    i2cReleaseBus (i2cDrv);
    if (msg != RDY_OK) i2cGetErr(i2cDrv, &SD_DRV);
      
    /*ulozeni namerenych hodnot do promenych*/
    *magX = (rxData[0] << 8) | rxData[1];
    *magY = (rxData[2] << 8) | rxData[3];
    *magZ = (rxData[4] << 8) | rxData[5];
}