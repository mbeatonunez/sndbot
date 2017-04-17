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
unsigned int area = 300;   
static int i = 0;           // iterate between signatures


void pixy_setup(void)
{ 
  pixy.init();
}

bool isTarget(void)                          //identify if a target is present
{
	
	if (pixy.getBlocks())
	{
		return true;
	}
 else
 {
    return false;
 }
	
}

bool isCenter(void)  			             // center the robot to the target
{
	pixy.getBlocks();
 int signature = pixy.blocks[i].signature;    //get target's signature
 if (signature == 1)
 {
	int x              = pixy.blocks[i].x;   //get x position
	int Xmin           = 140;                 // min x position
	int Xmax           = 180;                // max x position

  unsigned int width   = pixy.blocks[i].width;   // get width       
  unsigned int height  = pixy.blocks[i].height;  // get heigh 
  unsigned int newarea = width * height;         // compare distance from target
  
  while (x < Xmin)                            //turn left if x position < max x position    
    {
      pixy.getBlocks();
      x              = pixy.blocks[i].x;   //get x position
      turn_left();
    }
  while (x > Xmax)                       //turn right if x position > max x position
    {
      pixy.getBlocks();
      x              = pixy.blocks[i].x;
      turn_right();
    }
  if (newarea < (area))                       // go forward if too far
    {
      drive_forward();
    }

  if (newarea > (area))                 // go backward if too close
    {
      drive_backward();
    }
	if (x < Xmax && x > Xmin && newarea < (area+10) && newarea > (area-10))             // When target is centered
		{
      motor_stop;
			return true;
		}
   else
    return false;
 }
	
}

		
