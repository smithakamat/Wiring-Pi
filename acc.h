#ifndef _ACC_H_
#define _ACC_H_

//#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define GSCALE 2

void setup(void);
void init(void);
void readXYZ(void);


#endif //_ACC_H_

