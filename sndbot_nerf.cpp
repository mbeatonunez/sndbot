/*
 * Nerf Gun Code
 * 
 * Using the Nerf N-Strike Elite Stryfe Blaster
 * url: https://www.walmart.com/ip/Nerf-N-Strike-Elite-Stryfe-Blaster/29461799
 * 
 * Note : The button and switch under the main trigger was removed, and the cables that control
 *        the DC motor where connected to the Arduino
 * 
 * Moises Beato
 * April 2017
 */
#include "sndbot.h"
#include <Servo.h>

Servo nefttrigger;

uint8_t nerfmotor = 37;

static void nerf_fire(void);

void nerf_setup(void)
{
  nefttrigger.attach(35);   // attaches the servo on pin 35 to the servo object
  nefttrigger.write(0);
  pinMode(nerfmotor, OUTPUT);
}

static void nerf_fire(void)
{
  nefttrigger.write(80);
  delay(2000);
  nefttrigger.write(0);

}

void engage_target(void)
{
    motor_stop();
    delay(1000); 
    nerf_fire();    
    digitalWrite(LASER,LOW); 
    delay(1000);
    turn_left();
    delay(1500);
    drive_forward(); 
}

