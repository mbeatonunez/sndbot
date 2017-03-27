#include "sndbot.h"


void setup() {

 Serial.begin(9600);
 morot_setup();
 pixy_setup();
 sonar_setup();
}

void loop() {
  pixy_find();

}



