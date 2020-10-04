#ifndef _LIB_
#define _LIB_
#include "lib.c"
#include "struct-device.h"

void config(struct device *);
void connectNetwork(struct device *);
void initPeripherals(); 
void getData(struct device *);
void generateJson(struct device *);
bool sendtoEndpoint(struct device *);
void t_delay(int); 

#endif
