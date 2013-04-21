#include <stdio.h>
#include "acc.h"
#include <time.h>
void main(void)
{
	/*Set up the I2C device*/
	setup();
	sleep(1);
	/*Initialize the control registers*/
	init();

	while(1)
	{
		/*Read the X,Y,Z axes of the I2C device*/
		readXYZ();
		sleep(1);
	}
}

