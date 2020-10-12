#include <stdlib.h>
#include <stdio.h>
#include <wiringPiI2C.h>
#include <wiringPi.h>
#include "mpu6050.h"

int fd_mpu;
int id_mpu;

char buffer[100];
char* s;

bool check_mpu6050()
{
    short id_mpu = wiringPiI2CReadReg8(fd_mpu, MPU_ID);
    if(id_mpu == -1) 	
	return false;
    else
    	return true;
}

void init_mpu6050(bool ft)
{
	if (ft)
		fd_mpu = wiringPiI2CSetup(Device_Address);   /*Initializes I2C with device Address*/
    
    wiringPiI2CWriteReg8 (fd_mpu, SMPLRT_DIV, 0x07);	/* Write to sample rate register */
    wiringPiI2CWriteReg8 (fd_mpu, PWR_MGMT_1, 0x01);	/* Write to power management register */
    wiringPiI2CWriteReg8 (fd_mpu, CONFIG, 0);		/* Write to Configuration register */
    wiringPiI2CWriteReg8 (fd_mpu, GYRO_CONFIG, 24);	/* Write to Gyro Configuration register */
    wiringPiI2CWriteReg8 (fd_mpu, INT_ENABLE, 0x01);	/* Write to interrupt enable register */
} 

short read_raw_data(int addr)
{
    short high_byte,low_byte,value;
    high_byte = wiringPiI2CReadReg8(fd_mpu, addr);
    low_byte = wiringPiI2CReadReg8(fd_mpu, addr+1);
    value = (high_byte << 8) | low_byte;
    return value;
}

void print_mpu6050()
{
    if (check_mpu6050())
	printf("MPU6050 : OK");
    else
	printf("MPU6050 : Not detected (Accelerometer, Gyroscope sensor)");
}

char* get_mpu6050(int a)
{
    s = ""; 
    switch (a) 
    {	
    	case 0:	/* Aceler X */
    	sprintf(buffer, "%.2f", read_raw_data(ACCEL_XOUT_H) / 1638.4);
    	s=buffer;
        return s ; 
        case 1:	/* Aceler Y */
    	sprintf(buffer, "%.2f", read_raw_data(ACCEL_YOUT_H) / 1638.4);
    	s=buffer;
        return s ; 
        case 2:
	sprintf(buffer, "%.2f", read_raw_data(ACCEL_ZOUT_H) / 1638.4);
    	s=buffer;
        return s ; /* Aceler Z */
        case 3:
    	sprintf(buffer, "%.2f", read_raw_data(GYRO_XOUT_H) / 131.0);
    	s=buffer;
        return s ; /* Gyrosc X */
        case 4:
    	sprintf(buffer, "%.2f", read_raw_data(GYRO_YOUT_H) / 131.0);
    	s=buffer;
        return s ; /* Gyrosc Y */
        case 5:
    	sprintf(buffer, "%.2f", read_raw_data(GYRO_ZOUT_H) / 131.0);
    	s=buffer;
        return s ; /* Gyrosc Z */
    }
    return "0";
}

