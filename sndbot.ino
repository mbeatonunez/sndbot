#include "sndbot.h"


void setup() {

  Serial.begin(9600);
  motor_setup();
  pixy_setup();
  sonar_setup();
}

void loop() {


  pixy_scan();
  if (blocks)
  {
    //Serial.println("Target Detected");
     init_scan();
    while(blocks)
    {
      pixy_find();
    }
  }
    else
    {
      //Serial.println("Target lost");
      //obstacle_avoid();
    }
}



