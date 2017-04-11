/*
 * S&D Bot Ultrasonic Sensors
 * 
 * Moises Beato
 * March 2017
 */
#include "sndbot.h"
#include <NewPing.h>


// Trigger and Echo pins per sensor 
#define TRIGGER_FRONT     22
#define ECHO_FRONT        23
#define TRIGGER_RIGHT     24
#define ECHO_RIGHT        25
#define TRIGGER_LEFT      26
#define ECHO_LEFT         27

#define PING_MAX_DISTANCE 200
#define PING_MIN_DISTANCE 30  //Min distance from obstacle

  uint8_t interval =      50; // interval at which pings will be send

  long distance_front, duration_front; 
  long distance_right, duration_right;
  long distance_left,  duration_left;

  //distance and debugging functions
  
  static long right_sensor(void);
  static long left_sensor(void);
  static void sensor_debugging(void);

void sonar_setup(void)
{
  pinMode(TRIGGER_FRONT, OUTPUT);
  pinMode(TRIGGER_RIGHT, OUTPUT);
  pinMode(TRIGGER_LEFT, OUTPUT);

  pinMode(ECHO_FRONT, INPUT);
  pinMode(ECHO_RIGHT, INPUT);
  pinMode(ECHO_LEFT, INPUT);
 	//NewPing::timer_ms(interval, obstacle_avoid); //check for obstacles every 50 ms
}


void obstacle_avoid(void)
{
    /// ping echo cycle
    left_sensor();
    right_sensor();
    front_sensor();   

    //error checking, bound distance
    if (distance_front > PING_MAX_DISTANCE)
    {
      front_sensor();
    }
    
    if (distance_right > PING_MAX_DISTANCE)
    {
      right_sensor();
    }
    
    if (distance_left > PING_MAX_DISTANCE)
    {
      left_sensor();
    }

    //avoid obstacles, else drive forward
    if(distance_front != NO_ECHO && distance_front < (PING_MIN_DISTANCE+20)) 
  	{
        turn_left();     
  	}
  	else if(distance_right != NO_ECHO && distance_right < PING_MIN_DISTANCE) 
  	{
        turn_left();
    }
  	else if(distance_left != NO_ECHO && distance_left < (PING_MIN_DISTANCE+20)) 
  	{
        turn_right();
  	}		
  	else  
  	{
   	    drive_forward();
  	}
   // sensor_debugging();
}

/// check distance from object
long front_sensor(void)
{ 
    digitalWrite(TRIGGER_FRONT, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIGGER_FRONT, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_FRONT, LOW);
    duration_front = pulseIn(ECHO_FRONT, HIGH);
    distance_front = (duration_front/2) / 29.1;
    return  distance_front;
}
static long right_sensor(void)
{
    digitalWrite(TRIGGER_RIGHT, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIGGER_RIGHT, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_RIGHT, LOW);
    duration_right = pulseIn(ECHO_RIGHT, HIGH);
    distance_right = (duration_right/2) / 29.1;
    return distance_right;
}
static long left_sensor(void)
{
    digitalWrite(TRIGGER_LEFT, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIGGER_LEFT, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_LEFT, LOW);
    duration_left = pulseIn(ECHO_LEFT, HIGH);
    distance_left  = (duration_left/2) / 29.1;
    return distance_left;
}
/// end of distance check

static void sensor_debugging(void)
{
   // sensor debugging
 Serial.print("front: "); 
 Serial.print(distance_front);
 Serial.print("    ");  
 Serial.print("right: "); 
 Serial.print(distance_right); 
 Serial.print("    ");
 Serial.print("left: "); 
 Serial.println(distance_left); 
}

