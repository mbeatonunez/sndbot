                                                                                                                                                                                                                                                                                                                                  /*
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

int signature;
int x;                      // positon x axis
unsigned int width;         // object's width
unsigned int height;        // object's height
unsigned int area;          // initial distance from object
unsigned int newarea;       // compare distance from object
int Xmin = 70;              // min x position
int Xmax = 200;             // max x position
int maxArea = 0;                // max distance
int minArea = 0;                // min distance 
static int i = 0;           // iterate between signatures
uint16_t blocks;

void pixy_setup(void)
{ 
  pixy.init();
}

void pixy_find(void)
{
  pixy_scan(); 
   if(signature == 1)//looking for signature 1
  {
    newarea = width * height; //calculate the object area    
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
      if (newarea < maxArea)//go forward if object too small
         {
          drive_forward();
          Serial.print(newarea);
          Serial.print("   ");
          Serial.println(maxArea);
          if (newarea > maxArea) // stop when 28 inches or 70 cm away from target
             {
              motor_stop();
              Serial.println("Target Reached");
              delay(2500);
              Serial.println("Fire");
              turn_left();
              delay(500);
                          
             }
        }
  }

}

void pixy_scan(void)
{
  blocks = pixy.getBlocks();  //receive data from pixy 
  signature = pixy.blocks[i].signature;    //get object's signature
  x = pixy.blocks[i].x;                    //get x position
  width = pixy.blocks[i].width;            //get width
  height = pixy.blocks[i].height;          //get heigh
  return;
}

void init_scan(void)
{
    motor_stop();
    pixy_scan();
    area = width * height; //calculate the object area 
    maxArea = area + 100;
    minArea = area - 100;
    delay(500);
    Serial.println(area);

}
  
