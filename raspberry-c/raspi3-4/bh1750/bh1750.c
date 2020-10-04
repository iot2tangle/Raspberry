#include <stdio.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <wiringPiI2C.h>
#include "bh1750.h"

int fd_bh;
int id_bh;

char buffer[100];
char* s;

bool check_bh1750()
{
	printf("\n- BH1750 not detected\n");
    	return false;
}

void init_bh1750()
{
    fd_bh = wiringPiI2CSetup(0x40);

} 
	
char* get_bh1750()
{
    init_bh1750();
    fd_bh = wiringPiI2CSetup(0x40);

    s = "";
    
    	sprintf(buffer, "%.d", (uint8_t)wiringPiI2CReadReg8(fd_bh, 0x00) << 8 | (uint8_t)wiringPiI2CReadReg8(fd_bh, 0x00));
    	s=buffer;
        return s ; /* Light */

    return "0";
}

