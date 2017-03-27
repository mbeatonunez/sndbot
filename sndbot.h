/*
 * S&D Bot header
 * 
 * Moises Beato
 * February 2017
 */
#ifndef SNDBOT_HEADER
#define SNDBOT_HEADER

#include "Arduino.h"

#define VERSION 0.4

//global variables 
extern uint8_t speed;

// sndbot_pixy.c
void pixy_setup(void);
void pixy_find(void);

// sndbot_motors.c
void morot_setup(void);
void drive_forward(void);
void drive_backward(void);
void turn_left(void);
void turn_right(void);
void motor_stop(void); 
void rotate_right(int angleInDegrees);
void rotate_left(int angleInDegrees);

// sndbot_sonar.c
void sonar_setup(void);
void obstacle_avoid(void);

#endif
