/*
 * S&D Bot header
 * 
 * Moises Beato
 * February 2017
 */
#ifndef SNDBOT_HEADER
#define SNDBOT_HEADER

#include "Arduino.h"

#define VERSION 0.85

// state machines 
extern enum FSM { STATE_INIT, STATE_CENTER_TARGET, STATE_APPROACH_TARGET, STATE_ENGAGE_TARGET} state;

// global variable
extern uint8_t speed; 


// sndbot_display.c
void display_setup(void);
void update_display(void);

// sndbot_pixy.c
void pixy_setup(void);
bool isTarget(void);
bool isCenter(void);
bool isReached(void);

// sndbot_motors.c
void motor_setup(void);
void drive_forward(void);
void drive_backward(void);
void turn_left(void);
void turn_right(void);
void motor_stop(void); 

// sndbot_sonar.c
void sonar_setup(void);
void obstacle_avoid(void);

#endif
