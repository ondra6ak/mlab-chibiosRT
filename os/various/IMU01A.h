/*
Part of library for the MLAB module IMU01A

Created by Ondra Sestak 2013
*/
#ifndef _IMU01A_H_
#define _IMU01A_H_
#endif

#define IMU01A_ACC 0x1C
#define IMU01A_ACC_AXIS 0x01 

#define IMU01A_GYRO 0x68
#define IMU01A_GYRO_X_L 0x28
#define IMU01A_GYRO_X_H 0x29
#define IMU01A_GYRO_Y_L 0x2a
#define IMU01A_GYRO_Y_H 0x2b
#define IMU01A_GYRO_Z_L 0x2c
#define IMU01A_GYRO_Z_H 0x2d
#define IMU01A_GYRO_TEMP 0x26


void accInit (I2CDriver *i2c_drv, uint8_t addr);
void accRead (I2CDriver *i2c_drv, uint8_t addr, float *acc_x, float *acc_y, float *acc_z);
void gyroInit (I2CDriver *i2c_drv, uint8_t addr);
void gyroRead (I2CDriver *i2c_drv, uint8_t addr, float *gyro_x, float *gyro_y, float *gyro_z);
void tempRead (I2CDriver *i2c_drv, uint8_t addr, uint8_t *temp);