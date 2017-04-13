/*
 * S&D Bot pixy functions
 * 
 * Using the CMUcam5 Pixy from ChemLabs
 * url: http://charmedlabs.com/default/pixy-cmucam5/
 *
 * Notes: The Pixy is connected to the Serial3 port (Tx3, Rx3) of the Arduino Mega, 
 *        to avoid issues with the Serial1 port when compiling and uploading updates 
 *        to the code. As a consequence, the PixyUART.h library was modified to use the
 *        Serial3 port, rather then the Serial1 port.  
 * 
 * code inspired by CytronTechologies
 * Original code found https://github.com/CytronTechnologies/Arduino_Pixy_CMUcam5_Sensor
 * 
 * Moises Beato
 * March 2017
 */
#include "sndbot.h"
#include <PixyUART.h>        // refer to notes avove

PixyUART pixy;               // using Serial3 port

// pixy vatiables
unsigned int area;          // predefined area of target 
static int i = 0;           // iterate between signatures


void pixy_setup(void)
{ 
  pixy.init();
}

bool isTarget(void)                          //identify if a target is present
{
	bool target_state = false;
	uint16_t blocks   = pixy.getBlocks();
	if (blocks)
	{
		motor_stop();
		target_state  = true;
	}
	return target_state;
}

bool isCenter(void)  			             // center the robot to the target
{
	uint16_t blocks    = pixy.getBlocks();
	int x              = pixy.blocks[i].x;   //get x position
	int Xmin           = 70;                 // min x position
	int Xmax           = 200;                // max x position
	bool center_status = false; 
	if (x < Xmin)                            //turn left if x position < max x position    
		{
			turn_left();
		}
	else if (x > Xmax) 						 //turn right if x position > max x position
		{
			turn_right();
		}
	else  									 // When target is centered
		{
			motor_stop();
			center_status = true;
		}
	return center_status;
}

bool isReached(void)
{
	uint16_t blocks      = pixy.getBlocks();
	unsigned int width   = pixy.blocks[i].width;   //get width       
	unsigned int height  = pixy.blocks[i].height;  //get heigh 
	unsigned int newarea = width * height;         // compare distance from target
	bool reached_status = false;
	if (newarea < (area-10))					   //go forward if too far
		{
			drive_forward();
		}
	 else if(newarea > (area+10))				   //go backward if too close
		{
			drive_backward();
		}
	 else 
		{
			motor_stop();
			reached_status = true;
		}
	return reached_status;
}

		
