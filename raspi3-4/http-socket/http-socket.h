#ifndef _SOCKET_H_
#define _SOCKET_H_

#include <stddef.h>

bool socket_sender(const char*, int, const char*, long);
bool isEndpointOk(const char*, int);
size_t write_data(void *, size_t, size_t, void *);

#endif
