#include <stdio.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <wiringPi.h>
#include "gpio.h"

#define GREEN_LED 0		// GPIO 17 Raspberry Pi 3/4
#define RED_LED 2		// GPIO 2 Raspberry Pi 3/4


void init_LEDs()
{
    wiringPiSetup ();	// This init the library wiringPi
	
    // LEDs
    pullUpDnControl (GREEN_LED, PUD_DOWN);
    pinMode (GREEN_LED, OUTPUT);
    pullUpDnControl (RED_LED, PUD_DOWN);
    pinMode (RED_LED, OUTPUT);

    digitalWrite (GREEN_LED, 1);
    digitalWrite (RED_LED, 1);
    delay (1000);
    digitalWrite (GREEN_LED, 0);
    digitalWrite (RED_LED, 0);
	
}

void led_GPIO(int led, int mode)
{
    if (led == 0)
	digitalWrite (GREEN_LED, mode);
    else
	digitalWrite (RED_LED, mode);
}


bool read_GPIO(int pin)
{
    if (digitalRead (pin))
	return true;
    else
	return false;
}
