/*
 * S&D Bot pixy functions
 * 
 * Using the CMUcam5 Pixy from ChemLabs
 * url: http://charmedlabs.com/default/pixy-cmucam5/
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

enum FSM_PIXY state_pixy;


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

 void pixy_fsm(void)
{
	switch (state_pixy)
	{
		case STATE_PIXY_INIT:   //get area of target when first encountered
      Serial.println("Pixy init scan");
      display_state_pixy();
			motor_stop();
			init_scan();
      state_pixy = STATE_CENTER;
			break;
		case STATE_CENTER:  // center target
      display_state_pixy();
      Serial.println("Center State");
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
        display_clear_action();
        display_centered();
        Serial.println("Target Centered");
				motor_stop();
				state_pixy = STATE_GET_TARGET;
			}
			break;
		case STATE_GET_TARGET: // get to predefined range of target
       display_state_pixy();
			 pixy_scan();
       Serial.println("Get Target State");
			 newarea = width * height;
			 if (newarea < minArea)//go forward if object too small
			 {
        Serial.println("Too Far");
				drive_forward();
        Serial.print("New Area = ");
				Serial.print(newarea);
				Serial.print("   ");
        Serial.print("Max Area = ");
				Serial.println(maxArea);
			 }
			 else if(newarea > maxArea)//go backward if object too big
			 {
        Serial.println("Too Close");
				drive_backward();
        Serial.print("New Area = ");
				Serial.print(newarea);
				Serial.print("   ");
        Serial.println("Min Area = ");
				Serial.println(minArea); 
			 }
			 else 
			 {
        display_clear_action();
        display_target_reached();
        Serial.println("Tagert Reached");
				motor_stop();
				state_pixy = STATE_WAIT_ON_MAIN;
				state = STATE_FIRE; 
			 }			
			break;
		case STATE_WAIT_ON_MAIN:
      display_state_pixy();
      Serial.println("Wait on main");
			// Do nothing, wait on main FSM
			break;
	}
	return;
	
}

void pixy_scan(void)  						//scan for targets and get block parameters
{
  blocks = pixy.getBlocks();  				//receive data from pixy 
  if (blocks)
  {
    Serial.println("Found Blocks");
    signature = pixy.blocks[i].signature;    	//get object's signature
    x = pixy.blocks[i].x;                    	//get x position
    width = pixy.blocks[i].width;            	//get width
    height = pixy.blocks[i].height;          	//get heigh
  }
  else if (!blocks)								//if no target is found during scan, return to default parameters
  {
    Serial.println("NO BLOCKS -> EXIT TO MAIN");
    state = STATE_INIT;					
  	state_pixy = STATE_WAIT_ON_MAIN; 
  }
  display_target_state();
  return;
}

static void init_scan(void)					
{
    for (int j = 0; j < 5; j++)
	{
		pixy_scan();
		area = width * height; 				//calculate the object area 
		maxArea = area + 100;				  //set the max distance from target
		minArea = area - 1020;				//set the min distance from target
    Serial.print("Area = ");
		Serial.println(area);
		delay(200);
    }
    state_pixy = STATE_CENTER;
    return;
}
  
