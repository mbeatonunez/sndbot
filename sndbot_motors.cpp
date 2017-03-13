/*
 * S&D Bot motors
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
int motor_left[] = {2, 3, 4, 5};
int motor_right[] = {6, 7, 8, 9};

uint8_t speed = 192;   // max speed (255)

unsigned long previousMillis = 0;

void morot_setup(void) 
{
  for(int i = 0; i < 4; i++) //initialize all pins as outputs
  {
    pinMode(motor_left[i], OUTPUT);
    pinMode(motor_right[i], OUTPUT);
  }
}

void drive_backward(void) 
{
  //set pins 2, 4, 7 and 9 to HIGH
  //set pins 3, 5, 6, and 8 to LOW
  analogWrite(motor_left[0], speed);
  digitalWrite(motor_left[1], LOW); 
  analogWrite(motor_left[2], speed);  
  digitalWrite(motor_left[3], LOW);

  digitalWrite(motor_right[0], LOW);
  analogWrite(motor_right[1], speed);
  digitalWrite(motor_right[2], LOW);
  analogWrite(motor_right[3], speed);
}

void drive_forward(void) 
{
  //set pins 2, 4, 7 and 9 to LOW
  //set pins 3, 5, 6, and 8 to HIGH
  digitalWrite(motor_left[0], LOW);
  analogWrite(motor_left[1], speed);
  digitalWrite(motor_left[2], LOW);
  analogWrite(motor_left[3], speed);  
  
  analogWrite(motor_right[0], speed);
  digitalWrite(motor_right[1], LOW);
  analogWrite(motor_right[2], speed);
  digitalWrite(motor_right[3], LOW);
}
void turn_left(void) 
{
  // turn left side off
  // move right side forward
  analogWrite(motor_left[0], speed);
  digitalWrite(motor_left[1], LOW);
  analogWrite(motor_left[2], speed);
  digitalWrite(motor_left[3], LOW);
  
  analogWrite(motor_right[0], speed);
  digitalWrite(motor_right[1], LOW);
  analogWrite(motor_right[2], speed);
  digitalWrite(motor_right[3], LOW);
}

void turn_right(void) 
{
  // turn right side off
  // move left side forward  
  digitalWrite(motor_left[0], LOW);
  analogWrite(motor_left[1], speed);
  digitalWrite(motor_left[2], LOW);
  analogWrite(motor_left[3], speed);

  digitalWrite(motor_right[0], LOW);
  analogWrite(motor_right[1], speed);
  digitalWrite(motor_right[2], LOW);
  analogWrite(motor_right[3], speed);
}

void motor_stop(void)
{
  digitalWrite(motor_left[0], LOW); 
  digitalWrite(motor_left[1], LOW); 
  digitalWrite(motor_left[2], LOW);
  digitalWrite(motor_left[3], LOW);  
  
  digitalWrite(motor_right[0], LOW); 
  digitalWrite(motor_right[1], LOW);
  digitalWrite(motor_right[2], LOW); 
  digitalWrite(motor_right[3], LOW);
}

//angle is dependent on motor speed
void rotate_right(int angleInDegrees) {
  for(int i=0; i< angleInDegrees; i++) {
    turn_right();
    delay(25); // adjust with speed
  }
}
void rotate_left(int angleInDegrees) {
  for(int i=0; i< angleInDegrees; i++) {
    turn_left();
    delay(25); // adjust with speed
  }
}

