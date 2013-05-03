/*Description: This C file initilizes the accleromter and reads the X, Y and Z 
velocity values. 

Authors: Smitha Sunil Kamat, Jay Khandhar
*/


/*Preprocessor directives and user defined header files*/
#include <stdio.h>
#include "acc.h"
#include <time.h>

/*Main function*/
void main(void)
{
	/*Set up the I2C device - Acceleromter MMA8452Q on the I2C bus 1*/
	setup();

	/*Delay of 1 second*/
	sleep(1);

	/*Initialize the acceleromter*/
	init();

	while(1)
	{
		/*Read the X,Y,Z axes of the accelerometer*/
		readXYZ();
		sleep(1);
	}
}

