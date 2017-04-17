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

int motor_left[] = {8,9,10,11};
int motor_right[] = {7,6,5,4};

uint8_t speed;   // max speed (255). Set to half speed

void drive_forward(void) 
{
  analogWrite(motor_left[0], speed);
  analogWrite(motor_left[1], 0);
  analogWrite(motor_left[2], speed);
  analogWrite(motor_left[3], 0);  

  analogWrite(motor_right[0], speed);
  analogWrite(motor_right[1], 0);
  analogWrite(motor_right[2], speed);
  analogWrite(motor_right[3], 0);  
}

void drive_backward(void) 
{
  analogWrite(motor_left[0], 0);
  analogWrite(motor_left[1], speed);
  analogWrite(motor_left[2], 0);
  analogWrite(motor_left[3], speed);

  analogWrite(motor_right[0], 0);
  analogWrite(motor_right[1], speed);
  analogWrite(motor_right[2], 0);
  analogWrite(motor_right[3], speed);
 
}
void turn_right(void) 
{
  //right_side back, left_side forward 
  analogWrite(motor_left[0], speed);
  analogWrite(motor_left[1], 0);
  analogWrite(motor_left[2], speed);
  analogWrite(motor_left[3], 0);

  analogWrite(motor_right[0], 0);
  analogWrite(motor_right[1], speed);
  analogWrite(motor_right[2], 0);
  analogWrite(motor_right[3], speed);
}

void turn_left(void) 
{
   //left_side back, right_side forward 
  analogWrite(motor_left[0], 0);
  analogWrite(motor_left[1], speed);
  analogWrite(motor_left[2], 0);
  analogWrite(motor_left[3], speed);

  analogWrite(motor_right[0], speed);
  analogWrite(motor_right[1], 0);
  analogWrite(motor_right[2], speed);
  analogWrite(motor_right[3], 0); 
}

void motor_stop(void)
{
  analogWrite(motor_left[0], 0); 
  analogWrite(motor_left[1], 0); 
  analogWrite(motor_left[2], 0); 
  analogWrite(motor_left[3], 0);
  
  analogWrite(motor_right[0], 0); 
  analogWrite(motor_right[1], 0);
  analogWrite(motor_right[2], 0); 
  analogWrite(motor_right[3], 0);

}

