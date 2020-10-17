#include <stdio.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <wiringPi.h>
#include "acoustic.h"

#define ACOUSTIC_ENABLE 4	// GPIO 23 Raspberry Pi 3/4
#define ACOUSTIC_DATA 5	// GPIO 24 Raspberry Pi 3/4

char buffer[100];
char* s;

bool check_acoustic()
{
    if (!digitalRead (ACOUSTIC_ENABLE))
	return true;
    else
	return false;
}

void init_acoustic(bool ft)
{
	if (ft)
	{
		pullUpDnControl(ACOUSTIC_ENABLE, PUD_UP);
		pinMode (ACOUSTIC_ENABLE, INPUT);
    
		pinMode (ACOUSTIC_DATA, INPUT);
	}
}

void print_acoustic()
{
    if (check_acoustic())
	printf("SOUND Sensor : OK");
    else
	printf("SOUND Sensor : Not detected");
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


