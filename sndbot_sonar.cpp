/*
 * S&D Bot Ultrasonic Sensors
 * 
 * Code inspired by !geek
 * url: http://tech.endeepak.com/blog/2016/01/02/simple-obstacle-avoiding-robot-using-arduino/
 * 
 * Moises Beato
 * March 2017
 */
#include "sndbot.h"
#include <NewPing.h>

// Trigger and Echo pins per sensor 
#define TRIGGER_PIN1      12
#define ECHO_PIN1         13
#define TRIGGER_PIN2      14
#define ECHO_PIN2         15
#define TRIGGER_PIN3      16
#define ECHO_PIN3         17
#define PING_MAX_DISTANCE 200 // Maximum distance we want to ping for in cm (about 79 inches)
#define PING_MIN_DISTANCE 20  //Min distance from obstacle

uint8_t interval =       50;  // interval at which pings will be send

//define each sensor object
NewPing sonar_front(TRIGGER_PIN1, ECHO_PIN1, PING_MAX_DISTANCE);
NewPing sonar_right(TRIGGER_PIN2, ECHO_PIN2, PING_MAX_DISTANCE);
NewPing sonar_left (TRIGGER_PIN3, ECHO_PIN3, PING_MAX_DISTANCE);

void sonar_setup(void)
{
	timer_ms(interval, obstacle_avoid); //check for obstacles every 50 ms
}


void obstacle_avoid(void)
{
	unsigned int distance_front = sonar_front.ping_cm();
	unsigned int distance_right = sonar_right.ping_cm();
	unsigned int distance_left  = sonar_left.ping_cm();
	if(distance_front != NO_ECHO && distance_front < PING_MIN_DISTANCE) 
	{
	rotate_right(180);
	}
	else if(distance_right != NO_ECHO && distance_right < PING_MIN_DISTANCE) 
	{
	rotate_left(90);
	}
	else if(distance_left != NO_ECHO && distance_left < PING_MIN_DISTANCE) 
	{
	rotate_right(90);
	}		
	else  
	{
	drive_forward();
	}			
}
