#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "config.h"
#include "lib.h"
#include "struct-device.h"


struct device dev;

int main ()
{
	
	config(&dev);			/* Configure Name of the device, Endpoint address and Wifi credentials (if its a WiFi Connection), return string with the endpoint */	
	initPeripherals();	/* Init GPIOs, I2C and ADC */
	connectNetwork(&dev);	/* Will drop out of this structure only when it has connected to the network and checks the existence of the endpoint */ 
	
 
	while (1)
	{	    
		getData(&dev);
		
		generateJson(&dev);

		if ( !sendtoEndpoint(&dev) )	/* Send JSON to the Endpoint, return boolean with the success of the operation */
			connectNetwork(&dev);	/* Only enters it detects a network error */

		t_delay(dev.interv); 
	}
        
	return 0;
}
