/*
 * Project: Search and Destroy Robot 
 * Creator: Moises Beato
 * Date Started: Febuary 2017
 * Department: Miami Dade College, School of Engineering Technology
 * Course: Applied Robotics
 * URL: http://courses.jamesmpoe.com/robotics/index.php?title=S%26D_Bot
 * 
 * Description: The S&D Bot is meant to enter a room, find targets, and shoot it.
 *              It uses obstacle avoidance to navigate the room, and a pixy cam to
 *              identify the target.
 * License:
 *        Copyright 2017 Moises Beato
 *        This program is free software: you can redistribute it and/or modify
 *        it under the terms of the GNU General Public License as published by
 *        the Free Software Foundation, either version 3 of the License, or
 *        (at your option) any later version.
 *
 *        This program is distributed in the hope that it will be useful,
 *        but WITHOUT ANY WARRANTY; without even the implied warranty of
 *        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *        GNU General Public License for more details.
 *
 *        You should have received a copy of the GNU General Public License
 *        along with this program.  If not, see <http://www.gnu.org/licenses>
 */

#include "sndbot.h"

enum FSM state;            // main state machine

void setup() {

  Serial.begin(9600);
  motor_setup();
  pixy_setup();
  sonar_setup();
  display_setup();
  state = STATE_INIT;
}

void loop() {
	
// main state machine
	switch(state)
	{
		case STATE_INIT:          // enter obstacle avoidance
			obstacle_avoid();
      display_state_main();   // display current state on LCD
			pixy_scan();            // search for targets
      if (blocks)
      {
        state = STATE_WAIT_ON_BLOCKS;
      }
			break;
    case STATE_WAIT_ON_BLOCKS: // transition state to isolate functions in init state
      display_state_main();
      state_pixy = STATE_PIXY_INIT;
      state = STATE_WAIT_ON_PIXY;
      break;
		case STATE_WAIT_ON_PIXY:   // wait for pixy to find target
			display_state_main();
      pixy_fsm();
			break;
		case STATE_FIRE:           // engage target
      display_state_main();
			delay(2500);             // simulate firing at target
      display_clear_action();  // clear action section of LCD 
			turn_right();            // face away from target and continue searching
			delay(1000);
			state = STATE_INIT;
			break;		
	} 
}



