/*
Library for the MLAB module IMU01A
This library lets you configure the sensors on the direct and fastest data streaming and read out the values

Created by Ondra Sestak 2013
*/

#include <ch.h>
#include <hal.h>
#include <chprintf.h>
#include <IMU01A.h>
#include <i2cGetErr.h>

/*accelerometer configuration*/
void accInit(I2CDriver *i2c_drv, uint8_t addr)
{
    uint8_t tx_data[8]; 
    msg_t msg;
    
    tx_data[0] = 0x2a;/*register CTRL_REG1*/
    tx_data[1] = 0x01;
    i2cAcquireBus (i2c_drv);
    msg = i2cMasterTransmitTimeout (i2c_drv, addr, tx_data, 2, 0, 0, MS2ST(4));
    i2cReleaseBus (i2c_drv);
    if (msg != RDY_OK) i2cGetErr (i2c_drv, &SD_DRV);
}

/*accelerometer reading*/
void accRead (I2CDriver *i2c_drv, uint8_t addr, float *acc_x, float *acc_y, float *acc_z)
{
    uint8_t tx_data[8]; 
    uint8_t rx_data[6];
    msg_t msg;

   	tx_data[0] = IMU01A_ACC_AXIS;
   	i2cAcquireBus (i2c_drv);
    msg = i2cMasterTransmitTimeout (i2c_drv, addr, tx_data, 1, rx_data, 6, MS2ST(4));
    i2cReleaseBus (i2c_drv);
    if (msg != RDY_OK) i2cGetErr(i2c_drv, &SD_DRV);
      
    *acc_x = (rx_data[0] << 8) | rx_data[1];
    *acc_y = (rx_data[2] << 8) | rx_data[3];
    *acc_z = (rx_data[4] << 8) | rx_data[5];
}

/*gyroscope configuration*/
void gyroInit (I2CDriver *i2c_drv, uint8_t addr)
{
    uint8_t tx_data[8]; 
    msg_t msg;
    
    tx_data[0] = 0x20;/*register CTRL_REG1*/
    tx_data[1] = 0xff;
    i2cAcquireBus (i2c_drv);
    msg = i2cMasterTransmitTimeout (i2c_drv, addr, tx_data, 2, 0, 0, MS2ST(4));
    i2cReleaseBus (i2c_drv);
    if (msg != RDY_OK) i2cGetErr (i2c_drv, &SD_DRV);

    tx_data[0] = 0x2e;/*register FIFO_CTRL_REG*/
    tx_data[1] = 0x40;
    i2cAcquireBus (i2c_drv);
    msg = i2cMasterTransmitTimeout (i2c_drv, addr, tx_data, 2, 0, 0, MS2ST(4));
    i2cReleaseBus (i2c_drv);
    if (msg != RDY_OK) i2cGetErr (i2c_drv, &SD_DRV);
}

/*gyroscope reading*/
void gyroRead (I2CDriver *i2c_drv, uint8_t addr, float *gyro_x, float *gyro_y, float *gyro_z)
{
    uint8_t tx_data[8]; 
    uint8_t rx_data[6];
    uint8_t lsb;
    msg_t msg;

    /*reading most significant byte X*/
    tx_data[0] = IMU01A_GYRO_X_H;
    i2cAcquireBus (i2c_drv);
    msg = i2cMasterTransmitTimeout (i2c_drv, addr, tx_data, 1, rx_data, 6, MS2ST(4));
    if (msg != RDY_OK) i2cGetErr(i2c_drv, &SD_DRV);
    lsb = rx_data[0];
    /*reading least significant byte X*/
    tx_data[0] = IMU01A_GYRO_X_L;
    msg = i2cMasterTransmitTimeout (i2c_drv, addr, tx_data, 1, rx_data, 6, MS2ST(4));
    i2cReleaseBus (i2c_drv);
    if (msg != RDY_OK) i2cGetErr(i2c_drv, &SD_DRV);
    *gyro_x = (lsb << 8) | rx_data[0];
    
    /*reading most significant byte Y*/
    tx_data[0] = IMU01A_GYRO_Y_H;
    i2cAcquireBus (i2c_drv);
    msg = i2cMasterTransmitTimeout (i2c_drv, addr, tx_data, 1, rx_data, 6, MS2ST(4));
    if (msg != RDY_OK) i2cGetErr(i2c_drv, &SD_DRV);
    lsb = rx_data[0];
    /*reading least significant byte Y*/
    tx_data[0] = IMU01A_GYRO_Y_L;
    msg = i2cMasterTransmitTimeout (i2c_drv, addr, tx_data, 1, rx_data, 6, MS2ST(4));
    i2cReleaseBus (i2c_drv);
    if (msg != RDY_OK) i2cGetErr(i2c_drv, &SD_DRV);
    *gyro_y = (lsb << 8) | rx_data[0];

    /*reading most significant byte Z*/
    tx_data[0] = IMU01A_GYRO_Z_H;
    i2cAcquireBus (i2c_drv);
    msg = i2cMasterTransmitTimeout (i2c_drv, addr, tx_data, 1, rx_data, 6, MS2ST(4));
    if (msg != RDY_OK) i2cGetErr(i2c_drv, &SD_DRV);
    lsb = rx_data[0];
    /*reading least significant byte Z*/
    tx_data[0] = IMU01A_GYRO_Z_L;
    msg = i2cMasterTransmitTimeout (i2c_drv, addr, tx_data, 1, rx_data, 6, MS2ST(4));
    i2cReleaseBus (i2c_drv);
    if (msg != RDY_OK) i2cGetErr(i2c_drv, &SD_DRV);
    *gyro_z= (lsb << 8) | rx_data[0];
}

/*temperature reading*/
void tempRead (I2CDriver *i2c_drv, uint8_t addr, uint8_t *temp)
{
    uint8_t tx_data[8]; 
    uint8_t rx_data[2];
    msg_t msg;

    tx_data[0] = IMU01A_GYRO_TEMP;
    i2cAcquireBus (i2c_drv);
    msg = i2cMasterTransmitTimeout (i2c_drv, addr, tx_data, 1, rx_data, 2, MS2ST(4));
    i2cReleaseBus (i2c_drv);
    if (msg != RDY_OK) i2cGetErr(i2c_drv, &SD_DRV);
      
    *temp = rx_data[0];
}