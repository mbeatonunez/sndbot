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
#define PING_MIN_DISTANCE 40  //Min distance from obstacle

uint8_t interval =       50;  // interval at which pings will be send

  long distance_front, duration_front; 
  long distance_right, duration_right;
  long distance_left,  duration_left;

  long front_sensor(void);
  long right_sensor(void);
  long left_sensor(void);

void sonar_setup(void)
{
  pinMode(TRIGGER_PIN1, OUTPUT);
  pinMode(TRIGGER_PIN2, OUTPUT);
  pinMode(TRIGGER_PIN3, OUTPUT);

  pinMode(ECHO_PIN1, INPUT);
  pinMode(ECHO_PIN2, INPUT);
  pinMode(ECHO_PIN3, INPUT);
 	NewPing::timer_ms(interval, obstacle_avoid); //check for obstacles every 50 ms
}


void obstacle_avoid(void)
{
    /// ping echo cycle
    left_sensor();
    right_sensor();
    front_sensor();
         
    distance_front = (duration_front/2) / 29.1;
    distance_right = (duration_right/2) / 29.1;
    distance_left  = (duration_left/2) / 29.1;

    //error checking
    if (distance_front > 200)
    {
      front_sensor();
      distance_front = (duration_front/2) / 29.1; 
    }
    
    if (distance_right > 200)
    {
      right_sensor();
      distance_right = (duration_right/2) / 29.1; 
    }
    
    if (distance_left > 200)
    {
      left_sensor();
      distance_left = (duration_left/2) / 29.1; 
    }

    
  if(distance_front != NO_ECHO && distance_front < (PING_MIN_DISTANCE+20)) 
	{
      motor_stop();
      delay(1000);
      drive_backward();
      delay(1500);
      motor_stop();
      turn_left();
      delay(1500);
	}
	else if(distance_right != NO_ECHO && distance_right < PING_MIN_DISTANCE) 
	{
    motor_stop();
    delay(1000);
    turn_left();
    delay(1000);
	}
	else if(distance_left != NO_ECHO && distance_left < PING_MIN_DISTANCE) 
	{
    motor_stop();
    delay(1000);
    turn_right();
    delay(1000);
	}		
	else  
	{
 	  drive_forward();
	}
 Serial.print("front: "); 
 Serial.print(distance_front);
 Serial.print("    ");  
 Serial.print("right: "); 
 Serial.print(distance_right); 
 Serial.print("    ");
 Serial.print("left: "); 
 Serial.println(distance_left);   
 
}
long front_sensor(void)
{
    digitalWrite(TRIGGER_PIN1, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIGGER_PIN1, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_PIN1, LOW);
    duration_front = pulseIn(ECHO_PIN1, HIGH);
    return  duration_front;
}
long right_sensor(void)
{
    digitalWrite(TRIGGER_PIN2, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIGGER_PIN2, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_PIN2, LOW);
    duration_right = pulseIn(ECHO_PIN2, HIGH);
    return duration_right;
}
long left_sensor(void)
{
    digitalWrite(TRIGGER_PIN3, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIGGER_PIN3, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_PIN3, LOW);
    duration_left = pulseIn(ECHO_PIN3, HIGH);
    return duration_left;
}

