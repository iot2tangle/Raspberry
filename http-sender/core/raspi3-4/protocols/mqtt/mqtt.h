#ifndef _MQTT_H_
#define _MQTT_H_

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

bool socket_sender(const char*, int, const char*, const char*, const char*, char*, long);
bool init_socket(const char*, int, const char*, const char*,bool);

#endif
