#include <stdio.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h> 
#include <unistd.h>
#include "basics.h"
#include "bme280/bme280.h"
#include "mpu6050/mpu6050.h"
#include "bh1750/bh1750.h"
#include "acoustic/acoustic.h"

char buffer[100];
char* s;

void welcome_msg()
{
    printf("\n					----  Raspberry Pi 3/4 -- IOT2TANGLE  --  HTTP  ----\n\n");
} 

void d_collect_msg(long* n)
{
    printf ("\n\nData collect - %ld\n", *n);
}

void print_sensors_state()
{
    printf ("   Sensors Detection:\n");
    print_bme280();
    print_mpu6050();
    print_bh1750();
    print_acoustic();
    printf ("\n");
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
