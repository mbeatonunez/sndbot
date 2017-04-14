/*
 * S&D Bot motors
 * 
 * Using Chassis, Motors and Dual motor driver from the Kingduino 4WD Ultrasonic Robot Kit
 * url: https://hobbyking.com/en_us/kingduino-4wd-ultrasonic-robot-kit.html
 * 
 * Code inspired by !geek
 * url: http://tech.endeepak.com/blog/2016/01/02/simple-obstacle-avoiding-robot-using-arduino/
 * 
 * Moises Beato
 * February 2017
 */
#include "sndbot.h"

// pins for the right and left side of the drivetrain
// using the skid-steer configuration

int motor_left[] = {5,6};
int motor_right[] = {3,4};
int enableA = 2;
int enableB = 7;

uint8_t speed;   // max speed (255). Set to half speed

void motor_setup(void) 
{
  pinMode(enableA, OUTPUT);
  pinMode(enableB, OUTPUT);
  digitalWrite(enableA, HIGH);
  digitalWrite(enableB, HIGH);
  
}

void drive_backward(void) 
{
  analogWrite(motor_left[0], speed);
  analogWrite(motor_left[1], 0); 

  analogWrite(motor_right[0], speed);
  analogWrite(motor_right[1], 0); 
}

void drive_forward(void) 
{
  analogWrite(motor_left[0], 0);
  analogWrite(motor_left[1], speed);

  analogWrite(motor_right[0], 0);
  analogWrite(motor_right[1], speed);
 
}
void turn_right(void) 
{
  //right_side back, left_side forward 
  analogWrite(motor_left[0], 0);
  analogWrite(motor_left[1], speed);

  analogWrite(motor_right[0], speed);
  analogWrite(motor_right[1], 0);
}

void turn_left(void) 
{
   //left_side back, right_side forward 
  analogWrite(motor_left[0], speed);
  analogWrite(motor_left[1], 0); 

  analogWrite(motor_right[0], 0);
  analogWrite(motor_right[1], speed);
}

void motor_stop(void)
{
  analogWrite(motor_left[0], 0); 
  analogWrite(motor_left[1], 0); 
  
  analogWrite(motor_right[0], 0); 
  analogWrite(motor_right[1], 0);

}

