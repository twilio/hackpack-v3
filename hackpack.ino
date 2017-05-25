#include "application.h"
#include <string.h>
#include <stdint.h>
#include "neopixel.h"
#include "cmd.h"
#include "pixel_grid.h"
#include "states.h"

//*****************************************
//We have some particle specific stuff here
PRODUCT_ID(3920);
PRODUCT_VERSION(8);
SYSTEM_MODE(SEMI_AUTOMATIC);

//*********************************************************************************
// Put your custom lighting sequence here, it can be an animation or a static image
// Display it by texting 'animate custom' to your device
// Color Format is 24-bit RGB (written in hex)
//*********************************************************************************
uint32_t custom_animation_lut[][16] = {
  { 0xFF0000,0x101010,0x101010,0x101010,
    0x101010,0x101010,0x101010,0x101010,
    0x101010,0x101010,0x101010,0x101010,
    0x101010,0x101010,0x101010,0x101010},   //Frame1

  { 0x101010,0x990000,0x101010,0x101010,
    0x990000,0x101010,0x101010,0x101010,
    0x101010,0x101010,0x101010,0x101010,
    0x101010,0x101010,0x101010,0x101010},   //Frame2

  { 0x101010,0x101010,0x660000,0x101010,
    0x101010,0x660000,0x101010,0x101010,
    0x660000,0x101010,0x101010,0x101010,
    0x101010,0x101010,0x101010,0x101010},   //Frame3

  { 0x101010,0x101010,0x101010,0x330000,
    0x101010,0x101010,0x330000,0x101010,
    0x101010,0x330000,0x101010,0x101010,
    0x330000,0x101010,0x101010,0x101010},   //Frame4

  { 0x101010,0x101010,0x101010,0x101010,
    0x101010,0x101010,0x101010,0x660000,
    0x101010,0x101010,0x660000,0x101010,
    0x101010,0x660000,0x101010,0x101010},   //Frame5

  { 0x101010,0x101010,0x101010,0x101010,
    0x101010,0x101010,0x101010,0x101010,
    0x101010,0x101010,0x101010,0x990000,
    0x101010,0x101010,0x990000,0x101010},   //Frame6

  { 0x101010,0x101010,0x101010,0x101010,
    0x101010,0x101010,0x101010,0x101010,
    0x101010,0x101010,0x101010,0x101010,
    0x101010,0x101010,0x101010,0xFF0000}    //Frame7

};

uint16_t custom_animation_length = (sizeof(custom_animation_lut) / sizeof(custom_animation_lut[0]));    //The number of frames in the above array
uint16_t custom_animation_framerate = 200;                                                              //Time (in mS) between frames - Feel free to tweak this!

//****************************************************************************************
//Our setup function runs once on power up of the Hackpack it initialises the whole system
void setup()
{
    init_system();

    block_scale = 1;
    block_glow = 0;
    block_jitter = 0;
}

//***************************************************************************
//Our loop function runs in a loop all the time while our Hackpack is powered
void loop()
{
    update_display();
}
