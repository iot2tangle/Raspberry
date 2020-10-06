#include <stdio.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <wiringPiI2C.h>
#include "mpu6050.h"

int fd_mpu;
int8_t power;
int id_mpu;

char buffer[100];
char* s;

void init_mpu6050()
{
    fd_mpu = wiringPiI2CSetup(0x68);
    power = wiringPiI2CReadReg8(fd_mpu, MPU_POWER1);
    wiringPiI2CWriteReg8(fd_mpu, MPU_POWER1, ~(1 << 6) & power);  
} 


bool check_mpu6050()
{
    //fd_mpu = wiringPiI2CSetup(0x68);	/* Check I2C Address */
    int id_mpu = (uint8_t)wiringPiI2CReadReg8(fd_mpu, MPU_ID);
    if(id_mpu == 255) 
    {
		printf("     - MPU6050 not detected (Accelerometer, Gyroscope sensor)\n");
		return false;
	}
    else
    	return true;
}

	
char* get_mpu6050(int a)
{
	//init_mpu6050();
    //fd_mpu = wiringPiI2CSetup(0x68);

    s = "";
    
    switch (a) 
    {	
    	case 0:
    	sprintf(buffer, "%.d", (uint8_t)wiringPiI2CReadReg8(fd_mpu, MPU_ACCEL_XOUT1) << 8 | (uint8_t)wiringPiI2CReadReg8(fd_mpu, MPU_ACCEL_XOUT2));
    	s=buffer;
        return s ; /* Aceler X */
        case 1:
    	sprintf(buffer, "%.d", (uint8_t)wiringPiI2CReadReg8(fd_mpu, MPU_ACCEL_YOUT1) << 8 | (uint8_t)wiringPiI2CReadReg8(fd_mpu, MPU_ACCEL_YOUT2));
    	s=buffer;
        return s ; /* Aceler Y */
        case 2:
    	sprintf(buffer, "%.d", (uint8_t)wiringPiI2CReadReg8(fd_mpu, MPU_ACCEL_ZOUT1) << 8 | (uint8_t)wiringPiI2CReadReg8(fd_mpu, MPU_ACCEL_ZOUT2));
    	s=buffer;
        return s ; /* Aceler Z */
        case 3:
    	sprintf(buffer, "%.d", (uint8_t)wiringPiI2CReadReg8(fd_mpu, MPU_GYRO_XOUT1) << 8 | (uint8_t)wiringPiI2CReadReg8(fd_mpu, MPU_GYRO_XOUT2));
    	s=buffer;
        return s ; /* Gyrosc X */
        case 4:
    	sprintf(buffer, "%.d", (uint8_t)wiringPiI2CReadReg8(fd_mpu, MPU_GYRO_YOUT1) << 8 | (uint8_t)wiringPiI2CReadReg8(fd_mpu, MPU_GYRO_YOUT1));
    	s=buffer;
        return s ; /* Gyrosc Y */
        case 5:
    	sprintf(buffer, "%.d", (uint8_t)wiringPiI2CReadReg8(fd_mpu, MPU_GYRO_ZOUT1) << 8 | (uint8_t)wiringPiI2CReadReg8(fd_mpu, MPU_GYRO_ZOUT2));
    	s=buffer;
        return s ; /* Gyrosc Z */
    }

    return "0";
}

