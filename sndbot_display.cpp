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

//internal function
static void display_init(void);

void display_setup(void) {
  tft.begin(HX8357D);
  tft.setRotation(3);
  tft.fillScreen(HX8357_BLACK);
  display_init();
}


void display_init(void) //displays the empty blocks for states, sensors, blocks status and actions
{  
  //display state block
  tft.setTextSize(3);
  tft.setTextColor(HX8357_WHITE,HX8357_BLACK);
  tft.setCursor(100,20);
  tft.println("STATE");
  tft.drawRect(10,50,430,50,HX8357_WHITE);
  tft.setCursor(15,60);
  tft.println("Current: ");
 
  // Target stattus block
  tft.setTextSize(3);
  tft.setCursor(100,130);
  tft.println("TARGET");
  tft.drawRect(10,160,430,40,HX8357_WHITE);
  tft.setTextSize(2);
  tft.setCursor(15,170);
  tft.println("Status: ");
 
  return;
}

void update_display(void)
{ 
  tft.setTextSize(2);
  switch(state)
  {
    case STATE_INIT:      
      tft.setCursor(170,65);
  		tft.println("STATE_INIT           ");
      tft.setCursor(110, 170);
      tft.println("No Target      ");
  		break;
    case STATE_CENTER_TARGET:
      tft.setCursor(110, 170);
      tft.println("Target Located ");
      tft.setCursor(170,65);
      tft.println("STATE_CENTER_TARGET   ");
  		break;
	  case STATE_ENGAGE_TARGET:
      tft.setCursor(170,65);
  		tft.println("STATE_ENGAGE_TARGET   ");
  		break;  
  }
  return;
}


