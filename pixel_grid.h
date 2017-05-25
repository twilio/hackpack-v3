#ifndef PIXEL_GRID_H_
#define PIXEL_GRID_H_

#include "neopixel.h"

#define PIXEL_PIN         A5
#define PIXEL_COUNT       16
#define PIXEL_TYPE        WS2812B
#define MAX_BRIGHTNESS    200   //NOTE: Maximum brightness (255) on all pixels may cause overheating by pulling excessive current from the Electron power supply!!

//Frame rates for the individual animation sequences (in mS)
#define CHASE_FRAMERATE       100
#define FADE_FRAMERATE        2
#define DOCK_FRAMERATE        250


//**************************************************************************************
//Globals for the custom frame data - these get defined by the user in the main ino file
extern uint32_t custom_animation_lut[][16];
extern uint16_t custom_animation_framerate;
extern uint16_t custom_animation_length;

//*********************
//Pixel color variables
extern Adafruit_NeoPixel grid;
extern uint32_t grid_color;
extern uint8_t grid_brightness;

//************************************
//Create globals for some basic colors
extern uint32_t BLACK;

//************************************
//Functions for our various animations
void init_pixels(void);
void chase_pixels(uint32_t c);
void fade_pixels(uint32_t c);
void set_all_pixels(uint32_t c, uint8_t brightness);
void docked_sequence(void);
void alert1_sequence(void);
void alert2_sequence(void);
void alert3_sequence(void);
void claim_sequence(void);
void custom_sequence(void);
void startup_display(void);
uint32_t time_since(uint32_t start_time);


//**********************************************************
//Look up table for our breathing sequence brightness values
const uint8_t PROGMEM fade_lut[] = {
  0,0,0,1,1,1,2,2,2,2,3,3,4,4,4,5,5,6,6,7,7,8,9,9,10,11,
  11,12,13,14,15,15,16,17,18,19,20,22,23,24,25,27,28,29,
  31,32,34,35,37,39,41,43,44,46,48,50,53,55,57,59,62,64,
  67,69,72,75,77,80,83,86,89,92,95,98,101,105,108,111,114,
  118,121,125,128,132,135,139,142,146,149,153,156,160,163,
  167,170,174,177,180,184,187,190,193,197,200,203,205,208,
  211,213,216,218,221,223,225,227,229,230,232,233,235,236,
  237,238,239,239,240,240,240,240,240,240,239,239,238,237,
  236,235,233,232,230,229,227,225,223,221,218,216,213,211,
  208,205,203,200,197,193,190,187,184,180,177,174,170,167,
  163,160,156,153,149,146,142,139,135,132,128,125,121,118,
  114,111,108,105,101,98,95,92,89,86,83,80,77,75,72,69,67,
  64,62,59,57,55,53,50,48,46,44,43,41,39,37,35,34,32,31,
  29,28,27,25,24,23,22,20,19,18,17,16,15,15,14,13,12,11,
  11,10,9,9,8,7,7,6,6,5,5,4,4,4,3,3,2,2,2,2,1,1,1,0,0,0
};

#define LEN_FADE_SEQ  (sizeof(fade_lut) / sizeof(fade_lut[0]))

//****************************************************
//Look up table for our chase sequence pixel locations
const uint8_t PROGMEM chase_lut[] = {
  4,5,6,7,8,9,10,11,12,13,14,15,8,9,10,11,4,5,6,7,0,1,2,3
};

#define LEN_CHASE_SEQ  (sizeof(chase_lut) / sizeof(chase_lut[0]))


//*************************************
//Look up table for our docked sequence
const uint32_t PROGMEM docked_lut[][16] = {
  { 0x000000,0x000000,0x000000,0x000000,
    0x000000,0x000000,0x000000,0x000000,
    0x000000,0x000000,0x000000,0x000000,
    0x000000,0x000000,0x000000,0x000000},   //Frame1

  { 0x333333,0x333333,0x333333,0x333333,
    0x000000,0x000000,0x000000,0x000000,
    0x000000,0x000000,0x000000,0x000000,
    0x000000,0x000000,0x000000,0x000000},    //Frame2

  { 0x666666,0x666666,0x666666,0x666666,
    0x666666,0x666666,0x666666,0x666666,
    0x000000,0x000000,0x000000,0x000000,
    0x000000,0x000000,0x000000,0x000000},    //Frame3

  { 0x999999,0x999999,0x999999,0x999999,
    0x999999,0x999999,0x999999,0x999999,
    0x999999,0x999999,0x999999,0x999999,
    0x000000,0x000000,0x000000,0x000000},    //Frame4

  { 0xCCCCCC,0xCCCCCC,0xCCCCCC,0xCCCCCC,
    0xCCCCCC,0xCCCCCC,0xCCCCCC,0xCCCCCC,
    0xCCCCCC,0xCCCCCC,0xCCCCCC,0xCCCCCC,
    0xCCCCCC,0xCCCCCC,0xCCCCCC,0xCCCCCC}    //Frame5

};

#define LEN_DOCKED_SEQ  (sizeof(docked_lut) / sizeof(docked_lut[0]))    //Number of rows/frames
#define REPS_DOCKED_SEQ     1

//*************************************
//Look up table for our alert1 sequence
const uint32_t PROGMEM alert1_lut[][16] = {
  { 0x101010,0x101010,0x101010,0x101010,
    0x101010,0x101010,0x101010,0x101010,
    0x101010,0x101010,0x101010,0x101010,
    0xFF0000,0x101010,0x101010,0x101010},    //Frame1

  { 0x101010,0x101010,0x101010,0x101010,
    0x101010,0x101010,0x101010,0x101010,
    0xFF0000,0xFF0000,0x101010,0x101010,
    0x101010,0xFF0000,0x101010,0x101010},    //Frame2

  { 0x101010,0x101010,0x101010,0x101010,
    0xFF0000,0xFF0000,0xFF0000,0x101010,
    0x101010,0x101010,0xFF0000,0x101010,
    0x101010,0x101010,0xFF0000,0x101010},    //Frame3

  { 0xFF0000,0xFF0000,0xFF0000,0xFF0000,
    0x101010,0x101010,0x101010,0xFF0000,
    0x101010,0x101010,0x101010,0xFF0000,
    0x101010,0x101010,0x101010,0xFF0000},      //Frame4

  { 0x101010,0x101010,0x101010,0x101010,
    0x101010,0x101010,0x101010,0x101010,
    0x101010,0x101010,0x101010,0x101010,
    0x101010,0x101010,0x101010,0x101010}      //Frame5
};

#define LEN_ALERT1_SEQ  (sizeof(alert1_lut) / sizeof(alert1_lut[0]))    //Number of rows/frames
#define REPS_ALERT1_SEQ     20
#define ALERT1_FRAMERATE    100

//***********************************************
//Look up table for our reminder/startup sequence
const uint32_t PROGMEM alert2_lut[][16] = {
  { 0x000000,0x000000,0x000000,0x666666,
    0x000000,0x000000,0x000000,0x666666,
    0x000000,0x000000,0x000000,0x666666,
    0x000000,0x000000,0x000000,0x666666},    //Frame1

  { 0x000000,0x000000,0x666666,0x000000,
    0x000000,0x000000,0x666666,0x000000,
    0x000000,0x000000,0x666666,0x666666,
    0x000000,0x000000,0x666666,0x000000},    //Frame2

  { 0x000000,0x666666,0x000000,0x666666,
    0x000000,0x666666,0x000000,0x666666,
    0x000000,0x666666,0x666666,0x666666,
    0x000000,0x666666,0x000000,0x666666},    //Frame3

  { 0x666666,0x000000,0x666666,0x000000,
    0x666666,0x000000,0x666666,0x000000,
    0x666666,0x666666,0x666666,0x000000,
    0x666666,0x000000,0x666666,0x000000},     //Frame4

  { 0x000000,0x666666,0x000000,0x666666,
    0x000000,0x666666,0x000000,0x000000,
    0x666666,0x666666,0x000000,0x000000,
    0x000000,0x666666,0x000000,0x666666},

  { 0x666666,0x000000,0x666666,0x666666,
    0x666666,0x000000,0x000000,0x666666,
    0x666666,0x000000,0x000000,0x666666,
    0x666666,0x000000,0x666666,0x666666},

  { 0x000000,0x666666,0x666666,0x666666,
    0x000000,0x000000,0x666666,0x000000,
    0x000000,0x000000,0x666666,0x000000,
    0x000000,0x666666,0x666666,0x666666},

  { 0x666666,0x666666,0x666666,0x000000,
    0x000000,0x666666,0x000000,0x000000,
    0x000000,0x666666,0x000000,0x000000,
    0x666666,0x666666,0x666666,0x000000},

  { 0x666666,0x666666,0x000000,0x000000,
    0x666666,0x000000,0x000000,0x000000,
    0x666666,0x000000,0x000000,0x000000,
    0x666666,0x666666,0x000000,0x000000},

  { 0x666666,0x000000,0x000000,0x000000,
    0x000000,0x000000,0x000000,0x000000,
    0x000000,0x000000,0x000000,0x000000,
    0x666666,0x000000,0x000000,0x000000},

  { 0x000000,0x000000,0x000000,0x000000,
    0x000000,0x000000,0x000000,0x000000,
    0x000000,0x000000,0x000000,0x000000,
    0x000000,0x000000,0x000000,0x000000}
};

#define LEN_ALERT2_SEQ  (sizeof(alert2_lut) / sizeof(alert2_lut[0]))    //Number of rows/frames
#define REPS_ALERT2_SEQ     2
#define ALERT2_FRAMERATE    300
#define ALERT2_DELAY        300000

//**************************************
//Look up tables for our alert3 sequence
const uint32_t PROGMEM alert3_lut[][16] = {
  { 0x000000,0x000000,0x000000,0x000000,
    0x000000,0x000001,0x000001,0x000000,
    0x000000,0x000001,0x000001,0x000000,
    0x000000,0x000000,0x000000,0x000000},    //Frame1

  { 0x000001,0x000001,0x000001,0x000001,
    0x000001,0x000000,0x000000,0x000001,
    0x000001,0x000000,0x000000,0x000001,
    0x000001,0x000001,0x000001,0x000001}    //Frame2
};

const uint32_t PROGMEM alert3_color_lut[] = {
    0xFFA500,     //Orange
    0xFFA500,
    0xFFCC00,     //Orange - Yellow
    0xFFCC00,
    0xFFFF00,     //Yellow
    0xFFFF00,
    0xADFF2F,     //Yellow - Green
    0xADFF2F,
    0x00FF00,     //Green
    0x00FF00,
    0x40E0D0,     //Green - Blue
    0x40E0D0,
    0x0000FF,     //Blue
    0x0000FF,
    0x7B68EE,     //Blue - Violet
    0x7B68EE,
    0x800080,     //Violet
    0x800080,
    0xD02090,     //Violet - Red
    0xD02090,
    0xFF0000,     //Red
    0xFF0000,
    0xFF4500,      //Red - Orange
    0xFF4500
};

#define LEN_ALERT3_SEQ  (sizeof(alert3_lut) / sizeof(alert3_lut[0]))                 //Number of rows/frames
#define COLORS_ALERT3_SEQ  (sizeof(alert3_color_lut) / sizeof(alert3_color_lut[0]))    //Number of colors
#define REPS_ALERT3_SEQ     4
#define ALERT3_FRAMERATE    5

//**********************
//Pixel Grid Layout:
// LED0 LED7 LED8  LED15
// LED1 LED6 LED9  LED14
// LED2 LED5 LED10 LED13
// LED3 LED4 LED11 LED12
//**********************

//*******************************************************
//Remap our grid to make visualisation in the code easier
const uint8_t pixel_map[] = {
  0,7,8,15,
  1,6,9,14,
  2,5,10,13,
  3,4,11,12
};
#endif
