/*Description: The following C code utilizes the wriringPi library to access the 
hardware registers of the MMA8452Q 3 axis accelerometer. 
WiringPi is an Arduino wiring-like library written in C and released under the 
GNU LGPLv3 license which is usable from C and C++ and many other languages with suitable wrappers.

Authors: Smitha Sunil Kamat, Jay Khandhar
*/

/*Preprocessor dierctives and user defined header files*/
#include <stdio.h>
#include "acc.h"

/*Global variables*/
int fd; /*file descriptor for the i2c device*/
unsigned char temp;

/*Setup the accelerometer on the I2C bus of the RPi*/
void setup(void)
{
        int ret =0;
        ret= wiringPiSetup();

	/*Setting up the I2C device*/
	if((fd = wiringPiI2CSetup(0x1D)) < 0 )
	{	
		printf("Error in the setup\n");
	}
	else
	{
		printf("Success setting up i2c device with the fd = %d\n",fd);
	}
}

/*Initialize the accelerometer using the appropriate initialization sequence*/
void init(void)
{
	
	unsigned char fsr;

	/*Reading the WHO_AM_I register of the i2c device*/
	temp = wiringPiI2CReadReg8(fd, 0x0D);
	printf("The value of the WHO_AM_I register is %d\n", temp);	

	if(temp == 0x2A)
		printf("The accelerometer is online\n");
	else
		printf("Coudnot connect to the device\n");

	/*Read the CTRL_REG1*/
	/*The accelerometer should be driven to standby mode before making changes to any of its control registers*/
	temp = wiringPiI2CReadReg8(fd,0x2A);
	temp = temp & ~(0x01); 
	/*Clear the active bit of the CTR_REG1 to go into Standby mode*/
	wiringPiI2CWriteReg8 (fd,0x2A,temp);
		
	/*Setting up  GSCALE to configure the accelerometer in the +-2g range*/
	fsr = GSCALE;
	if(fsr > 8) fsr = 8;
	fsr = fsr >> 2;
	/*setting up the accelerometer to +-2g by writing to the XYZ_DATA_CFG register*/
	wiringPiI2CWriteReg8 (fd,0x0E,fsr);

	/*Read the CTRL_REG1 again*/
	temp = wiringPiI2CReadReg8(fd, 0x2A);
	temp = temp | 0x01;
	/*Bringing back the accelerometer into ACTIVE mode*/
	wiringPiI2CWriteReg8 (fd,0x2A,temp);

}

/*Function to read the X,Y,Z axes values*/
void readXYZ(void)
{
	unsigned int xlow,xhigh,ylow,yhigh,zlow,zhigh;
	unsigned int xconcat, yconcat, zconcat;

	xhigh = wiringPiI2CReadReg8(fd, 0x01);
	xlow = wiringPiI2CReadReg8(fd, 0x02);

	xconcat = (xhigh << 8) + xlow;
	xconcat = xconcat >> 4;

	yhigh = wiringPiI2CReadReg8(fd, 0x03);
	ylow = wiringPiI2CReadReg8(fd, 0x04);

	yconcat = (yhigh << 8) + ylow;
	yconcat = yconcat >> 4;

	zhigh = wiringPiI2CReadReg8(fd, 0x05);
	zlow = wiringPiI2CReadReg8(fd, 0x06);

	zconcat = (zhigh << 8) + zlow;
	zconcat = zconcat >> 4;

	printf("X : Y : Z : %d, %d, %d\n",xconcat, yconcat, zconcat);
}



