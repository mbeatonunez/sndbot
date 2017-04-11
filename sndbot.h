/*
 * S&D Bot header
 * 
 * Moises Beato
 * February 2017
 */
#ifndef SNDBOT_HEADER
#define SNDBOT_HEADER

#include "Arduino.h"

#define VERSION 0.6
// state machines
extern enum FSM { STATE_INIT, STATE_WAIT_ON_PIXY, STATE_FIRE} state;
extern enum FSM_PIXY { STATE_PIXY_INIT, STATE_CENTER, STATE_GET_TARGET, STATE_WAIT_ON_MAIN} state_pixy; 

//global variables 
extern uint8_t speed;
extern uint16_t blocks;

// sndbot_pixy.c
void pixy_setup(void);
void pixy_scan(void);

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
