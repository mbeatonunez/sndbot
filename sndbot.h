/*
 * S&D Bot header
 * 
 * Moises Beato
 * February 2017
 */
#ifndef SNDBOT_HEADER
#define SNDBOT_HEADER

#include "Arduino.h"

#define VERSION 1.0

// state machines 
extern enum FSM { STATE_INIT, STATE_CENTER_TARGET, STATE_ENGAGE_TARGET} state;

// global variable
extern uint8_t speed; 
extern uint8_t LASER;


// sndbot_display.c
void display_setup(void);
void update_display(void);

// sndbot_pixy.c
void pixy_setup(void);
bool isTarget(void);
bool isCenter(void);

// sndbot_motors.c
void drive_forward(void);
void drive_backward(void);
void turn_left(void);
void turn_right(void);
void motor_stop(void); 

// sndbot_nerf.c
void nerf_setup(void);
void engage_target(void); 

// sndbot_sonar.c
void sonar_setup(void);
void obstacle_avoid(void);

#endif
