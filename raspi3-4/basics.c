#include <stdio.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h> 
#include <unistd.h>
#include "basics.h"

char buffer[100];
char* s;

void welcome_msg()
{
   printf("\n					----  Raspberry Pi 3/4 -- IOT2TANGLE  --  HTTP  ----\n\n");
} 
	
void d_collect_msg(long* n)
{
   printf ("\n\nData collect - %ld\n   Sensors Detection:\n", *n);
}

void udelay_basics (long d)
{
   usleep(d);
}

long take_time_basics()
{
   time_t t;
   time(&t);
   return t;
}
