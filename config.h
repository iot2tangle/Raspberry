#ifndef _CONFIG_H
#define _CONFIG_H

/* ----- CONFIG FILE ----- */


/* Device */
const char* id_name = "PI3-4_HTTP";

/* Network */
const char* endpoint = "192.168.1.113/sensor_data";    /* Endpoint must not include 'http://xxx' */
int port = 8080;

bool isWifi = false; /* This is 'true' for microcontrollers like ESP32 or STM32. In RaspberryPi it will be 'false', because the network connection is made outside the program by the Raspberry OS */
const char* ssid_WiFi = "SSID-WIFI";
const char* pass_WiFi = "pass_WiFi";

/* Enable Sensors */
bool isEnable_TemperatureIntern = true;
bool isEnable_TemperatureExtern = true;	   /*                     true: Enable  --  false: Disable                            */
bool isEnable_Humidity = true;			   /* If the sensor is disabled the data about it will not be displayed in the Tangle */
bool isEnable_Pressure = true;
bool isEnable_Acoustic = true;
bool isEnable_Light = true;
bool isEnable_Accelerometer = true;
bool isEnable_Gyroscope = true;

/* Interval of time */
long interval = 30;    /* Time in seconds between */



#endif
