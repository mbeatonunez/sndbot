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
	update_display();
	// state machine
	switch(state)
	{
		case STATE_INIT:      			// perform obstacle avoidance until target is found
			obstacle_avoid();
			if (isTarget)
			{
				state = STATE_CENTER_TARGET;
			}
			break;
		case STATE_CENTER_TARGET:  		// center robot to target
			if (isCenter)
			{
				state = STATE_APPROACH_TARGET;
			}
			else if (!isTarget)    		// return to default state if target is lost
			{
				state = STATE_INIT;
			}
			break;
		case STATE_APPROACH_TARGET: 	// get target to range
			if (isReached)
			{
				state = STATE_ENGAGE_TARGET;
			}
			else if (!isTarget)    		// return to default state if target is lost
			{
				state = STATE_INIT;
			}
			break;
		case STATE_ENGAGE_TARGET:  		// fire on target
			engage_target();
			state = STATE_INIT;
			break;
		default:
			state = STATE_INIT;
			break;
	} 
}

void engage_target(void) //placeholder function until the taget engament sequence is completed
{
	//simulate target engagement
	//digitalWrite(gunMotor, HIGH);
	motor_stop(); //fire();
	delay (3000);	
	turn_left();
	delay(1000);	
}


