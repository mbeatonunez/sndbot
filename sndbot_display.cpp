/*
 * Display Code
 * 
 * Using Adafuit TFT 3.5in LCD Touchscreen HX8387
 * url: https://www.adafruit.com/product/2050?gclid=CNuqzqjcntMCFdgYgQodyD0Eyw
 * 
 * Moises Beato
 * April 2017
 */
#include "sndbot.h"
#include "Adafruit_GFX.h"
#include "Adafruit_HX8357.h"
#include "gfxfont.h"

//define tft comm pins
#define TFT_CS 48
#define TFT_DC 49
Adafruit_HX8357 tft = Adafruit_HX8357(TFT_CS, TFT_DC);

//internal functions
static void display_init(void);

void display_setup(void) {
  tft.begin(HX8357D);
  tft.setRotation(3);
  tft.fillScreen(HX8357_BLACK);
  display_init();
}

static void display_init(void) //displays the empty blocks for states, sensors, blocks status and actions
{  
  //display state block
  tft.setTextSize(3);
  tft.setCursor(80,20);
  tft.println("STATES");
  tft.drawRect(10,50,300,80,HX8357_WHITE);
  tft.setCursor(15,60);
  tft.println("Main: ");
  tft.setCursor(15,100);
  tft.println("Pixy: ");
  
  //sensor block
  tft.setCursor(350,20);
  tft.println("SENSORS");
  tft.drawRect(330,50,150,80,HX8357_WHITE);
  tft.setTextSize(2);
  tft.setCursor(340,60);
  tft.println("Front: ");
  tft.setCursor(340,85);
  tft.println("Left : "); 
  tft.setCursor(340,110);
  tft.println("Right: "); 
  
  // Target stattus block
  tft.setTextSize(2);
  tft.setCursor(80,140);
  tft.println("TARGET");
  tft.drawRect(10,160,300,40,HX8357_WHITE);
  tft.setTextSize(2);
  tft.setCursor(15,170);
  tft.println("Status: ");
  
  // display events block
  tft.setTextSize(3);
  tft.setCursor(80,210);
  tft.println("ACTIONS");
  tft.drawRect(10,240,300,60,HX8357_WHITE);     
  return;
}

//display in STATE block
void display_state_main(void)
{ //diplay the curret state of main FSM on LCD
  tft.setTextSize(2);
  tft.setCursor(110,65);
  switch(state)
  {
    case STATE_INIT:
      tft.fillRect(109,64,160,20,HX8357_BLACK);
      tft.println("Initial State ");
      break;
    case STATE_WAIT_ON_BLOCKS:
      tft.fillRect(109,64,160,20,HX8357_BLACK);
      tft.println("Wait on Blocks");
      Serial.println("Wait on blocks");
      break;
    case STATE_WAIT_ON_PIXY:
      tft.fillRect(109,64,160,20,HX8357_BLACK);
      tft.println("Wait on Pixy  ");
      Serial.println("Wait on pixy");
      break;
    case STATE_FIRE:
      tft.fillRect(109,64,160,20,HX8357_BLACK);
      tft.println("Fire State    ");
      display_clear_action();
      display_engaged();
      Serial.println("State Fire");
      break;  
  }
  return;
}

//display in STATE block
void display_state_pixy(void)
{ //diplay the curret state of pixy FSM on LCD
  tft.setTextSize(2);
  tft.setCursor(110,105);
  switch (state_pixy)
  {
    case STATE_PIXY_INIT:   
      tft.fillRect(109,104,160,20,HX8357_BLACK);
      tft.println("Initial State");
      break;
    case STATE_CENTER:
      tft.fillRect(109,104,160,20,HX8357_BLACK);
      tft.println("Center Target");
      break;
    case STATE_GET_TARGET:
      tft.fillRect(109,104,160,20,HX8357_BLACK);
      tft.println("Get Target   ");
      break;
    case STATE_WAIT_ON_MAIN:
      tft.fillRect(109,104,160,20,HX8357_BLACK);
      tft.println("Wait on main ");
      break;
  }
  return;
}

//display in TARGET block
void display_target_state(void)
{ //display of target is found of not
  tft.setTextSize(2);
  tft.setCursor(110, 170);
  if (blocks)
  {
    tft.println("Target Found");
  }
  else if (!blocks)
  {
    tft.fillRect(109, 169, 160, 20, HX8357_BLACK);
  }
  return;
}

void display_sensor_value(void) // display in sensor block
{ 
  tft.setTextSize(2);
  tft.fillRect(425, 60, 50, 65, HX8357_BLACK);
  tft.setCursor(425, 60);
  tft.print(distance_front);
  tft.setCursor(425, 85);
  tft.print(distance_left);
  tft.setCursor(425,110);
  tft.println(distance_right);
}

//display in action block when called
void display_avoid(void) 
{
  tft.setTextSize(2);
  tft.setCursor(40, 260);
  tft.println("Obstacle Avoidance");
  return;
}

void display_centered(void)
{
  tft.setTextSize(2);
  tft.setCursor(40, 260);
  tft.println("Target Centered");
  return;
}

void display_target_reached(void)
{
  tft.setTextSize(2);
  tft.setCursor(40, 260);
  tft.println("Target Reached");
  return;
}

void display_engaged(void)
{
  tft.setTextSize(2);
  tft.setCursor(40, 260);
  tft.println("Target engaged");
  return;
}

void display_clear_action(void)
{
  tft.fillRect(39, 259, 250, 20, HX8357_BLACK);
  return;
}
// end of action block code
