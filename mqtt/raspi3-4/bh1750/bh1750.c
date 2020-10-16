#include <stdio.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <wiringPiI2C.h>
#include "bh1750.h"

int fd_bh;
int id_bh;
int word;

char buffer[100];
char* s;

bool check_bh1750()
{
    if( wiringPiI2CReadReg16(fd_bh, 0x00) == -1 ) 
	return false;
    else
    	return true;
}

void init_bh1750(bool ft)
{
	if (ft)
		fd_bh = wiringPiI2CSetup(0x23);
} 

void print_bh1750()
{   
    if (check_bh1750())
	printf("BH1750 : OK");
    else
	printf("BH1750 : Not detected (Light sensor)");
}
	
char* get_bh1750()
{
    wiringPiI2CWrite(fd_bh, 0x21);   // One-time measurement at 0.5 lx resolution. Measurement Time is typically 120ms. It is automatically set to Power Down mode after measurement.
    sleep(1);
    word = wiringPiI2CReadReg16(fd_bh, 0x00);

    s = "";
    sprintf(buffer, "%d", ((word & 0xff00)>>8) | ((word & 0x00ff)<<8));
    s=buffer;
    return s ; /* Light */
}

