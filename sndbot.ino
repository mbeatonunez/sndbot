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
	
	while (1) // main state machine
	{
		switch(state)
		{
			case STATE_INIT: // enter obstacle avoidance
				obstacle_avoid();
				pixy_scan();
				if (blocks) // change states if target has been identified 
				{
					motor_stop();
					state_pixy = STATE_PIXY_INIT;
					state = STATE_WAIT_ON_PIXY;
				}
				break;
			case STATE_WAIT_ON_PIXY:
				// Do nothing, and wait on pixy to finish
				break;
			case STATE_FIRE:
				//replace with fire mechanism
				delay(2500);
				turn_right();
				delay(1000);
				state = STATE_INIT;
				break;
			
		}
		
	}  
}



