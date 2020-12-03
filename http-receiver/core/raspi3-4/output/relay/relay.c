#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <wiringPi.h>
#include "relay.h"

#define NUM_RELAYS 4
#define RELAY_1 21		// RELAY 1 in GPIO 5 Raspberry Pi 3/4 -- GPIO21 for WiringPi
#define RELAY_2 22		// RELAY 2 in GPIO 6 Raspberry Pi 3/4 -- GPIO22 for WiringPi
#define RELAY_3 23		// RELAY 3 in GPIO 13 Raspberry Pi 3/4 -- GPIO23 for WiringPi
#define RELAY_4 25		// RELAY 4 in GPIO 26 Raspberry Pi 3/4 -- GPIO25 for WiringPi

const int num[NUM_RELAYS] = { RELAY_1, RELAY_2, RELAY_3,  RELAY_4};

void init_relay()
{
	wiringPiSetup ();	// This init the library wiringPi - Inicializated before
	
	for (int i=0; i<NUM_RELAYS; i++)
	{
    	pullUpDnControl (num[i], PUD_DOWN);
    	pinMode (num[i], OUTPUT);;
	}
}

void set_relay_GPIO(int relay, int mode)
{
	digitalWrite (num[relay], mode);
}
