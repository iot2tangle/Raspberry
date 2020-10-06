#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h> 
#include <unistd.h>

#include "struct-device.h"
#include "config.h"
#include "raspi3-4/http-socket/http-socket.h"
#include "raspi3-4/tIntern/tIntern.h"
#include "raspi3-4/bme280/bme280.h"
#include "raspi3-4/mpu6050/mpu6050.h"
#include "raspi3-4/bh1750/bh1750.h"



void config(struct device *z)
{
	int i;

	z->id = id_name;

	z->ep = endpoint;
	z->ep_port = port;

	z->WiFi = isWifi;    /* In RaspberryPi it will be false, because the network connection is made outside the program by the Raspberry OS*/
	if (isWifi)
	{
        z->ssid = ssid_WiFi;
        z->pass = pass_WiFi;
    }
    else
    {
        z->ssid = "";
        z->pass = "";
    }

    z->isEnable[0] = isEnable_TemperatureIntern;
    z->isEnable[1] = isEnable_TemperatureExtern;
    z->isEnable[2] = isEnable_Humidity;
    z->isEnable[3] = isEnable_Pressure;
    z->isEnable[4] = isEnable_Acoustic;
    z->isEnable[5] = isEnable_Light;
    for (i=6; i<9; i++)
		z->isEnable[i] = isEnable_Accelerometer;
    for (i=9; i<12; i++)
		z->isEnable[i] = isEnable_Gyroscope;

    z->s_name[0] = "InternalTemperature";   // In ESP8266 -> "InternalVoltage"
    z->s_name[1] = "Temperature";
    z->s_name[2] = "Humidity";
    z->s_name[3] = "Pressure";
    z->s_name[4] = "SoundLevel";
    z->s_name[5] = "Light";
    z->s_name[6] = "X";
    z->s_name[7] = "Y";
    z->s_name[8] = "Z";
    z->s_name[9] = "X";
    z->s_name[10] = "Y";
    z->s_name[11] = "Z";

    z->interv = interval;

}

void initPeripherals(long* c) 
{
	*c = 0;		// Init counter
	//if RaspberryPi
	printf("\n				----  Raspberry Pi 3/4  -- IOT2TANGLE  --  \n\n");		// ESTO VA EN LOS ESPECIFICOS DE RASPBERRY

	//initGPIO();
	
	init_bme280();

	init_mpu6050();
	
	init_bh1750();
}


void connectNetwork(struct device *z)
{

//  while ( !connectAttempt() )    /* Attempt to connect to the network via WiFi, in RaspberryPi only check connection to the network. */
//  	error(1);

    if ( !isEndpointOk(z->ep, z->ep_port) )     /* Check Endpoint */
		printf(" "); //		error(2);

}




void getData(struct device *z, long *c)
{
	int i;
	
	printf ("\n\nData collect - %ld\n   Sensors Detection:\n", ++(*c));		// ESTO VA EN LOS ESPECIFICOS DE RASPBERRY
	
	
	/* GET DATA INTERNAL TEMPERATURE */
	strcpy(z->d[0], get_internal_temp());

	/* GET DATA BME280 */
	if (check_bme280())
	{
		for (i=0; i<3; i++)
			strcpy(z->d[i+1], get_bme280(i));
	}
	else
	{
		for (i=0; i<3; i++)
			strcpy(z->d[i+1], "0");
	}

	/* GET DATA ACOUSTIC */
	strcpy(z->d[4], "True");

	/* GET DATA LIGHT */
	if (check_bh1750())
		strcpy(z->d[5], get_bh1750());
	else
		strcpy(z->d[5], "0");

	/* GET DATA MPU6050 */
	if (check_mpu6050())
	{
		for (i=0; i<7; i++)
			strcpy(z->d[i+6], get_mpu6050(i));
	}
	else
	{
		for (i=0; i<7; i++)
			strcpy(z->d[i+6], "0");
	}
}


void generateJson(struct device *z)
{
	z->s_name[0]= "InternalTemperature"; // Valor Harcodeado porque este string se rompe cuando entra a la funcion, ya voy a ver porque, por ahora asi

	int i;

	strcpy(z->json, "{\"iot2tangle\":[");

	strcat(z->json, "{\"sensor\":\"Internal\",\"data\":[");
	for (i=0;i<1;i++)
	{
		if (i != 0) strcat(z->json, ",");
		strcat(z->json, "{\"");
		strcat(z->json, z->s_name[i]);
		strcat(z->json, "\":\"");
		strcat(z->json, z->d[i]);
		strcat(z->json, "\"}");
	}
	strcat(z->json, "]},");
	
	strcat(z->json, "{\"sensor\":\"Environmental\",\"data\":[");
	for (i=0;i<3;i++)
	{
		if (i != 0) strcat(z->json, ",");
		strcat(z->json, "{\"");
		strcat(z->json, z->s_name[i+1]);
		strcat(z->json, "\":\"");
		strcat(z->json, z->d[i+1]);
		strcat(z->json, "\"}");
	}
	strcat(z->json, "]},");
	
	strcat(z->json, "{\"sensor\":\"Acoustic\",\"data\":[");
	for (i=0;i<1;i++)
	{
		if (i != 0) strcat(z->json, ",");
		strcat(z->json, "{\"");
		strcat(z->json, z->s_name[i+4]);
		strcat(z->json, "\":\"");
		strcat(z->json, z->d[i+4]);
		strcat(z->json, "\"}");
	}
	strcat(z->json, "]},");
	
	strcat(z->json, "{\"sensor\":\"Light\",\"data\":[");
	for (i=0;i<1;i++)
	{
		if (i != 0) strcat(z->json, ",");
		strcat(z->json, "{\"");
		strcat(z->json, z->s_name[i+5]);
		strcat(z->json, "\":\"");
		strcat(z->json, z->d[i+5]);
		strcat(z->json, "\"}");
	}
	strcat(z->json, "]},");
	
	
	strcat(z->json, "{\"sensor\":\"Acelerometer\",\"data\":[");
	for (i=0;i<3;i++)
	{
		if (i != 0) strcat(z->json, ",");
		strcat(z->json, "{\"");
		strcat(z->json, z->s_name[i+6]);
		strcat(z->json, "\":\"");
		strcat(z->json, z->d[i+6]);
		strcat(z->json, "\"}");
	}
	strcat(z->json, "]},");

	strcat(z->json, "{\"sensor\":\"Gyroscope\",\"data\":[");
	for (i=0;i<3;i++)
	{
		if (i != 0) strcat(z->json, ",");
		strcat(z->json, "{\"");
		strcat(z->json, z->s_name[i+9]);
		strcat(z->json, "\":\"");
		strcat(z->json, z->d[i+9]);
		strcat(z->json, "\"}");
	}
	strcat(z->json, "]}");		// The last one without ','
	
	strcat(z->json, "],\"device\": \"");
	strcat(z->json, z->id);
	strcat(z->json, "\",\"timestamp\": \"0\"}");	

}


bool sendtoEndpoint(struct device *z)
{
	bool b_socket = socket_sender(z->ep, z->ep_port, z->json, z->interv);
	if (b_socket)
		printf(" ");	// Blink in green LED;
	else
		printf(" ");	// Blink in green RED - ERROR 1 (Bad connection with the endpoint);
	
	return b_socket;
}


void t_delay(long d, long l) 
{  
    usleep( (d - l) * 1000000 );	/* Time set by user  minus  loss time by operation */ 
}

long take_time() 
{  
   time_t t;
   time(&t);
   return t;
}
