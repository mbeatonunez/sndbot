/*
 * S&D Bot header
 * 
 * Moises Beato
 * February 2017
 */
#ifndef SNDBOT_HEADER
#define SNDBOT_HEADER

#include <HardwareSerial.h>
#include "Arduino.h"

#define VERSION 0.1

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


#endif
