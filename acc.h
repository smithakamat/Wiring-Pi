/*Description : This is the header file for the acc.c file that uses the 
Wiring Pi library to access teh accleromter's hardware registers

Authors: Smitha Sunil Kamat, Jay Khandhar
*/

#ifndef _ACC_H_
#define _ACC_H_

#include <wiringPi.h>
#include <wiringPiI2C.h>

#define GSCALE 2

void setup(void);
void init(void);
void readXYZ(void);


#endif //_ACC_H_

