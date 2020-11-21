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
    printf("\n					----  Raspberry 3/4 Receiver -- IOT2TANGLE  --");
    
    #ifdef HTTP	
    	printf("  HTTP  ----\n\n");	// Printf in shell
    #endif
    #ifdef MQTT	
    	printf("  MQTT  ----\n\n");	// Printf in shell
    #endif 
} 

void d_collect_msg(long* n)
{
    printf("---------------------------------------------------------------------------------------------------------------\n");
    printf ("Data collect from Tangle: - %ld\n", *n);
}

void print_json(char* js)
{
	printf ("Last Json recovered from Tangle:\n%s\n\n", js);
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
