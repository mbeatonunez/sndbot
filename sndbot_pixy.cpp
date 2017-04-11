/*
 * S&D Bot pixy functions
 * 
 * code inspired by CytronTechologies
 * Original code found https://github.com/CytronTechnologies/Arduino_Pixy_CMUcam5_Sensor
 * 
 * Moises Beato
 * March 2017
 */
#include "sndbot.h"
#include <SPI.h>  
#include <Pixy.h>

Pixy pixy;

enum FSM state_pixy;

static void pixy_fsm(void);
static void init_scan(void);

// pixy vatiables
int signature;
int x;                      // positon x axis
unsigned int width;         // object's width
unsigned int height;        // object's height
unsigned int area;          // initial distance from object
unsigned int newarea;       // compare distance from object
int Xmin = 70;              // min x position
int Xmax = 200;             // max x position
int maxArea = 0;            // max distance from target
int minArea = 0;            // min distance from target
static int i = 0;           // iterate between signatures
uint16_t blocks;

void pixy_setup(void)
{ 
  pixy.init();
  state_pixy = STATE_WAIT_ON_MAIN; 
}


static void pixy_fsm(void)
{
	switch (state_pixy)
	{
		case STATE_PIXY_INIT:   //get area of target when first encountered
			init_scan();
			state_pixy = STATE_CENTER;
			break;
		case STATE_CENTER:
			pixy_scan();
			if (x < Xmin)//turn left if x position < max x position    
			{
				turn_left();
				Serial.println("Turning left");
			}
			else if (x > Xmax) //turn right if x position > max x position
			{
				turn_right();
				Serial.println("Turning Right");
			}
			else  // When target is centered
			{
				motor_stop();
				state_pixy = STATE_GET_TARGET;
			}
			break;
		case STATE_GET_TARGET:
			 pixy_scan();
			 newarea = width * height;
			 if (newarea < minArea)//go forward if object too small
			 {
				drive_forward();
				Serial.print(newarea);
				Serial.print("   ");
				Serial.println(maxArea);
			 }
			 else if(newarea > maxArea)//go backward if object too big
			 {
				drive_backward();
				Serial.print(newarea);
				Serial.print("   ");
				Serial.println(minArea); 
			 }
			 else 
			 {
				motor_stop();
				state_pixy = STATE_WAIT_ON_MAIN;
				state = STATE_FIRE; 
			 }			
			break;
		case STATE_WAIT_ON_MAIN:
			// Do nothing, wait on main FSM
			break;
	}
	return;
	
}

void pixy_scan(void)  						//scan for targets and get block parameters
{
  blocks = pixy.getBlocks();  				//receive data from pixy 
  signature = pixy.blocks[i].signature;    	//get object's signature
  x = pixy.blocks[i].x;                    	//get x position
  width = pixy.blocks[i].width;            	//get width
  height = pixy.blocks[i].height;          	//get heigh
  if (!blocks)								//if no target is found during scan, return to default parameters
  {
	state = STATE_INIT;					
	state_pixy = STATE_WAIT_ON_MAIN; 
  }
  return;
}

static void init_scan(void)					
{
    for (int j = 0; j < 5: j++)
	{
		pixy_scan();
		area = width * height; 				//calculate the object area 
		maxArea = area + 100;				//set the max distance from target
		minArea = area - 120;				//set the min distance from target
		Serial.println(area);
		delay(200);
    }

}
  
