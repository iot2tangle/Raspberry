#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tIntern.h"

char buffer[400];
char *s;
float num;
FILE *fptr; 

char* get_internal_temp() 
{
	s = "";	

	if ((fptr = fopen("/sys/class/thermal/thermal_zone0/temp","r")) == NULL)
		return "NULL";
    
    fscanf(fptr,"%f", &num);
    fclose(fptr);
    sprintf(buffer, "%.2f", (num / 1000) );	
	s = buffer;
	return s;    
}
