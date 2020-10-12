#include <stdio.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <wiringPiI2C.h>
#include "bme280.h"

int fd_bme;
bme280_calib_data cal;
bme280_raw_data raw;
int32_t t_fine;
int id;

char buffer[100];
char* s;

bool check_bme280()
{   
    id = (uint16_t)wiringPiI2CReadReg16(fd_bme, BME280_REGISTER_CHIPID);
    if(id == 65535)			// When ID is 65535 is because BME280 is not connected
	return false;
    else
	return true;
}

void init_bme280(bool ft)
{   
	if (ft)
		fd_bme = wiringPiI2CSetup(0x76);

    readCalibrationData(fd_bme, &cal);

    wiringPiI2CWriteReg8(fd_bme, 0xf2, 0x01);   // humidity oversampling x 1
    wiringPiI2CWriteReg8(fd_bme, 0xf4, 0x25);   // pressure and temperature oversampling x 1, mode normal	  
}

void print_bme280()
{
    if (check_bme280())
	printf("BME280 : OK");
    else
	printf("BME280 : Not detected (Temperat, Humidity, Pressure sensor)");
}

char* get_bme280(int ind) 
{
    readCalibrationData(fd_bme, &cal);
    getRawData(fd_bme, &raw);
    t_fine = getTemperatureCalibration(&cal, raw.temperature);
   
    s = " ";
  
    if (ind == 0)
    {
	sprintf(buffer, "%.2f", compensateTemperature(t_fine));
	s=buffer;
	return s ; /* Celsius */
    }
    if (ind == 1)
    {
	sprintf(buffer, "%.2f", compensateHumidity(raw.humidity, &cal, t_fine) );
	s=buffer;
	return s ; /* % */
    }
    if (ind == 2)
    {
	sprintf(buffer, "%.1f", compensatePressure(raw.pressure, &cal, t_fine) / 100 );
	s=buffer;
	return s ; /* hPa */
    }
    return 0;
}


int32_t getTemperatureCalibration(bme280_calib_data *cal, int32_t adc_T) 
{
    int32_t var1  = ((((adc_T>>3) - ((int32_t)cal->dig_T1 <<1))) * ((int32_t)cal->dig_T2)) >> 11;

    int32_t var2  = (((((adc_T>>4) - ((int32_t)cal->dig_T1)) * ((adc_T>>4) - ((int32_t)cal->dig_T1))) >> 12) * ((int32_t)cal->dig_T3)) >> 14;

    return var1 + var2;
}

void readCalibrationData(int fd_bme, bme280_calib_data *data) {
    data->dig_T1 = (uint16_t)wiringPiI2CReadReg16(fd_bme, BME280_REGISTER_DIG_T1);
    data->dig_T2 = (int16_t)wiringPiI2CReadReg16(fd_bme, BME280_REGISTER_DIG_T2);
    data->dig_T3 = (int16_t)wiringPiI2CReadReg16(fd_bme, BME280_REGISTER_DIG_T3);

    data->dig_P1 = (uint16_t)wiringPiI2CReadReg16(fd_bme, BME280_REGISTER_DIG_P1);
    data->dig_P2 = (int16_t)wiringPiI2CReadReg16(fd_bme, BME280_REGISTER_DIG_P2);
    data->dig_P3 = (int16_t)wiringPiI2CReadReg16(fd_bme, BME280_REGISTER_DIG_P3);
    data->dig_P4 = (int16_t)wiringPiI2CReadReg16(fd_bme, BME280_REGISTER_DIG_P4);
    data->dig_P5 = (int16_t)wiringPiI2CReadReg16(fd_bme, BME280_REGISTER_DIG_P5);
    data->dig_P6 = (int16_t)wiringPiI2CReadReg16(fd_bme, BME280_REGISTER_DIG_P6);
    data->dig_P7 = (int16_t)wiringPiI2CReadReg16(fd_bme, BME280_REGISTER_DIG_P7);
    data->dig_P8 = (int16_t)wiringPiI2CReadReg16(fd_bme, BME280_REGISTER_DIG_P8);
    data->dig_P9 = (int16_t)wiringPiI2CReadReg16(fd_bme, BME280_REGISTER_DIG_P9);

    data->dig_H1 = (uint8_t)wiringPiI2CReadReg8(fd_bme, BME280_REGISTER_DIG_H1);
    data->dig_H2 = (int16_t)wiringPiI2CReadReg16(fd_bme, BME280_REGISTER_DIG_H2);
    data->dig_H3 = (uint8_t)wiringPiI2CReadReg8(fd_bme, BME280_REGISTER_DIG_H3);
    data->dig_H4 = (wiringPiI2CReadReg8(fd_bme, BME280_REGISTER_DIG_H4) << 4) | (wiringPiI2CReadReg8(fd_bme, BME280_REGISTER_DIG_H4+1) & 0xF);
    data->dig_H5 = (wiringPiI2CReadReg8(fd_bme, BME280_REGISTER_DIG_H5+1) << 4) | (wiringPiI2CReadReg8(fd_bme, BME280_REGISTER_DIG_H5) >> 4);
    data->dig_H6 = (int8_t)wiringPiI2CReadReg8(fd_bme, BME280_REGISTER_DIG_H6);
}

float compensateTemperature(int32_t t_fine) 
{
    float T  = (t_fine * 5 + 128) >> 8;
    return T/100;
}

float compensatePressure(int32_t adc_P, bme280_calib_data *cal, int32_t t_fine) 
{
    int64_t var1, var2, p;

    var1 = ((int64_t)t_fine) - 128000;
    var2 = var1 * var1 * (int64_t)cal->dig_P6;
    var2 = var2 + ((var1*(int64_t)cal->dig_P5)<<17);
    var2 = var2 + (((int64_t)cal->dig_P4)<<35);
    var1 = ((var1 * var1 * (int64_t)cal->dig_P3)>>8) + ((var1 * (int64_t)cal->dig_P2)<<12);
    var1 = (((((int64_t)1)<<47)+var1))*((int64_t)cal->dig_P1)>>33;

    if (var1 == 0) 
    {
    	return 0;  // avoid exception caused by division by zero
    }
    p = 1048576 - adc_P;
    p = (((p<<31) - var2)*3125) / var1;
    var1 = (((int64_t)cal->dig_P9) * (p>>13) * (p>>13)) >> 25;
    var2 = (((int64_t)cal->dig_P8) * p) >> 19;

    p = ((p + var1 + var2) >> 8) + (((int64_t)cal->dig_P7)<<4);
    return (float)p/256;
}


float compensateHumidity(int32_t adc_H, bme280_calib_data *cal, int32_t t_fine) 
{
    int32_t v_x1_u32r;

    v_x1_u32r = (t_fine - ((int32_t)76800));

    v_x1_u32r = (((((adc_H << 14) - (((int32_t)cal->dig_H4) << 20) -
      (((int32_t)cal->dig_H5) * v_x1_u32r)) + ((int32_t)16384)) >> 15) *
         (((((((v_x1_u32r * ((int32_t)cal->dig_H6)) >> 10) *
        (((v_x1_u32r * ((int32_t)cal->dig_H3)) >> 11) + ((int32_t)32768))) >> 10) +
      ((int32_t)2097152)) * ((int32_t)cal->dig_H2) + 8192) >> 14));

    v_x1_u32r = (v_x1_u32r - (((((v_x1_u32r >> 15) * (v_x1_u32r >> 15)) >> 7) *
           ((int32_t)cal->dig_H1)) >> 4));

    v_x1_u32r = (v_x1_u32r < 0) ? 0 : v_x1_u32r;
    v_x1_u32r = (v_x1_u32r > 419430400) ? 419430400 : v_x1_u32r;
    float h = (v_x1_u32r>>12);
    return  h / 1024.0;
}

void getRawData(int fd_bme, bme280_raw_data *raw) 
{
    wiringPiI2CWrite(fd_bme, 0xf7);

    raw->pmsb = wiringPiI2CRead(fd_bme);
    raw->plsb = wiringPiI2CRead(fd_bme);
    raw->pxsb = wiringPiI2CRead(fd_bme);

    raw->tmsb = wiringPiI2CRead(fd_bme);
    raw->tlsb = wiringPiI2CRead(fd_bme);
    raw->txsb = wiringPiI2CRead(fd_bme);

    raw->hmsb = wiringPiI2CRead(fd_bme);
    raw->hlsb = wiringPiI2CRead(fd_bme);

    raw->temperature = 0;
    raw->temperature = (raw->temperature | raw->tmsb) << 8;
    raw->temperature = (raw->temperature | raw->tlsb) << 8;
    raw->temperature = (raw->temperature | raw->txsb) >> 4;

    raw->pressure = 0;
    raw->pressure = (raw->pressure | raw->pmsb) << 8;
    raw->pressure = (raw->pressure | raw->plsb) << 8;
    raw->pressure = (raw->pressure | raw->pxsb) >> 4;

    raw->humidity = 0;
    raw->humidity = (raw->humidity | raw->hmsb) << 8;
    raw->humidity = (raw->humidity | raw->hlsb);
}

