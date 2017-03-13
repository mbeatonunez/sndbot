#include "sndbot.h"


void setup() {
 
 morot_setup();
 pixy_setup();
 sonar_setup();
}

void loop() {

  pixy_find();

}



