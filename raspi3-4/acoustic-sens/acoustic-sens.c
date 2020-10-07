#include <stdio.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <wiringPi.h>
#include "acoustic-sens.h"

#define ACOUSTIC_ENABLE 4	// GPIO 23 Raspberry Pi 3/4
#define ACOUSTIC_DATA 5	// GPIO 24 Raspberry Pi 3/4

char buffer[100];
char* s;

void init_acoustic()
{
    pullUpDnControl(ACOUSTIC_ENABLE, PUD_UP);
    pinMode (ACOUSTIC_ENABLE, INPUT);
    
    pinMode (ACOUSTIC_DATA, OUTPUT);
}

bool check_acoustic()
{
    if (!digitalRead (ACOUSTIC_ENABLE))
	return true;
    else
    {
	printf("     - Acoustic Sensor not detected\n");
	return false;
    }
}

char* get_acoustic()
{
    s = " ";
	
    if (digitalRead (ACOUSTIC_DATA))
	sprintf(buffer, "High");
    else
	sprintf(buffer, "Low");

    s=buffer;
    return s;
}


