#ifndef _HTTP_H_
#define _HTTP_H_

#include <stddef.h>

bool socket_sender(const char*, int, const char*, const char*, const char*, const char*, long);
bool init_socket(const char*, int, const char*, const char*, bool);
size_t write_data(void *, size_t, size_t, void *);

#endif
