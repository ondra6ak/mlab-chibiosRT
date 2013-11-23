#ifndef _IMU01A_H_
#define _IMU01A_H_
#endif

#define IMU01A_ACC 0x1C
#define IMU01A_ACC_AXIS 0x01 

#define IMU01A_GYRO 0x68
#define IMU01A_GYRO_AXIS 0x28
#define IMU01A_GYRO_TEMP 0x26


void accInit (I2CDriver *i2c_drv, uint8_t addr);
void accRead (I2CDriver *i2c_drv, uint8_t addr, int16_t *acc_x, int16_t *acc_y, int16_t *acc_z);
void gyroInit (I2CDriver *i2c_drv, uint8_t addr);
void gyroRead (I2CDriver *i2c_drv, uint8_t addr, int16_t *gyro_x, int16_t *gyro_y, int16_t *gyro_z);
void tempRead (I2CDriver *i2c_drv, uint8_t addr, uint8_t *temp);