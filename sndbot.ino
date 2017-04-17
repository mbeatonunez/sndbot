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

uint8_t LASER = 33;

enum FSM state;            // main state machine
uint8_t interruptPin = 3;

void bump_sensor(void); // ISR function for bump sensor

void setup() {

  Serial.begin(9600);
  pinMode(LASER, OUTPUT);
  digitalWrite(LASER,LOW);
  pixy_setup();
  sonar_setup();
  display_setup();
  nerf_setup();
  state = STATE_INIT;
  pinMode(interruptPin, INPUT_PULLUP);
  //attachInterrupt(digitalPinToInterrupt(interruptPin), bump_sensor, RISING);
}

void loop() {
 	// state machine
	switch(state)
	{
		case STATE_INIT:      			// perform obstacle avoidance until target is found
      if (isTarget())
			{
        digitalWrite(LASER,HIGH);        
        motor_stop();
        delay(2000); 
				state = STATE_CENTER_TARGET;
			}
      if (!isTarget())        // make the forward movement dependent the pixy
      {
        speed = 128;
        drive_forward();
      }
      obstacle_avoid();
      update_display();
			break;
    case STATE_CENTER_TARGET:     // center robot to target
      update_display();
      speed = 64;
      if (isCenter())
      { 
        state = STATE_ENGAGE_TARGET;
      }
      break;
    case STATE_ENGAGE_TARGET:  		// fire on target
			update_display();
      speed = 128;
			engage_target();
      delay(1000);    
			state = STATE_INIT;
			break;
		default:
			state = STATE_INIT;
			break;
	} 
}

void bump_sensor(void)
{
  cli();
  motor_stop();
  delay(1000);
  drive_forward();
  delay(2000);
  motor_stop();
  sei();
}

