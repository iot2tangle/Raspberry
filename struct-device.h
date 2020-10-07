#ifndef STRUCT_DEVICE_H_
#define STRUCT_DEVICE_H_

#include <stdio.h>
#include <stdbool.h>


struct device {
   const char *id;

   bool WiFi;
   const char *ssid;
   const char *pass;
   
   const char *ep;
   int ep_port;
   
   bool isEnable[12];
   char d[12][10];    /* Sensors Data String */
   const char *s_name[30];    /* Sensors Names */
   bool isConnected[12];

   long interv; 
   
   char json[1023];
}; 

#endif
