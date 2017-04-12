/*
 * S&D Bot header
 * 
 * Moises Beato
 * February 2017
 */
#ifndef SNDBOT_HEADER
#define SNDBOT_HEADER

#include "Arduino.h"

#define VERSION 0.7

// state machines 
extern enum FSM { STATE_INIT, STATE_WAIT_ON_BLOCKS, STATE_WAIT_ON_PIXY, STATE_FIRE} state;
extern enum FSM_PIXY { STATE_PIXY_INIT, STATE_CENTER, STATE_GET_TARGET, STATE_WAIT_ON_MAIN} state_pixy; 

//global variables 
extern uint8_t speed;
extern uint16_t blocks;
extern long distance_front; 
extern long distance_right;
extern long distance_left;


// sndbot_display.c
void display_setup(void);
void display_state_main(void);
void display_state_pixy(void);
void display_target_state(void);
void display_sensor_value(void);
void display_avoid(void);
void display_clear_action(void);
void display_centered(void);
void display_target_reached(void);
void display_engaged(void);

// sndbot_pixy.c
void pixy_setup(void);
void pixy_scan(void);
void pixy_fsm(void);

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
