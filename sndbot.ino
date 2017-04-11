#include "sndbot.h"

enum FSM state;

void setup() {

  Serial.begin(9600);
  motor_setup();
  pixy_setup();
  sonar_setup();
  state = STATE_INIT;
}

void loop() {
	
// main state machine
	switch(state)
	{
		case STATE_INIT: // enter obstacle avoidance
			obstacle_avoid();
			pixy_scan();
      if (blocks)
        state = STATE_WAIT_ON_BLOCKS;
			break;
    case STATE_WAIT_ON_BLOCKS:
        Serial.println("Wait on blocks");
        state_pixy = STATE_PIXY_INIT;
        state = STATE_WAIT_ON_PIXY;
      break;
		case STATE_WAIT_ON_PIXY:
			//wait on pixy to finish
      Serial.println("Wait on pixy");
      pixy_fsm();
			break;
		case STATE_FIRE:
			//replace with fire mechanism
     Serial.println("State Fire");
			delay(2500);
			turn_right();
			delay(1000);
			state = STATE_INIT;
			break;
		
	} 
}



