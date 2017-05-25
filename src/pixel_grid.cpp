#include "pixel_grid.h"
#include "states.h"
#include "cmd.h"

//***********************
//State Machine Variables
SYSTEM_STATE CURRENT_MODE = BLOCK;

//***********************
//Pixel control variables
Adafruit_NeoPixel grid = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);
uint32_t grid_color = 0x000000;             //Default to off
uint8_t grid_brightness = MAX_BRIGHTNESS;

//************************************
//Create globals for some basic colors
uint32_t BLACK = grid.Color(0, 0, 0);

//***************************
//Animation control variables
static uint16_t frame = 0;
static uint32_t begin = 0;
static uint16_t repeat = 0;
static uint16_t color = 0;
static uint32_t reminder_time = 0;

//***********************************************************************
//Initialise the LEDs and clear the display
//(this happens before trying to connect so that they don't get stuck on)
void init_pixels(void)
{
  awake(1);
  grid.begin();
  delay(500);                           //Wait to ensure the Neopixel is initialised
  set_all_pixels(BLACK, MAX_BRIGHTNESS);
  delay(500);
}

//******************************************
//Set the color and brightness of all pixels
void set_all_pixels(uint32_t c, uint8_t brightness)
{
  uint8_t i;

  //***************************
  //Set the brightness globally
  if(brightness>0)
  {
    if(brightness < MAX_BRIGHTNESS)
    {
      grid.setBrightness(brightness);
    }
    else
    {
      grid.setBrightness(MAX_BRIGHTNESS);
    }
  }

  //*********************************
  //Set each pixel color individually
  for(i=0; i<grid.numPixels(); i++)
  {
    grid.setPixelColor(i, c);
  }

  grid.show();
}

//*********************************************************
//Step through a chase sequence for the pixels individually
void chase_pixels(uint32_t c)
{
  uint8_t i;

  //************************************
  //Initialise if this is our first pass
  if(state_transition_flag == 1)
  {
    grid.setBrightness(grid_brightness);
    state_transition_flag = 0;
    begin = millis();
    frame = 20;
  }

  //******************************************
  //Update our animation at the set frame rate
  if(time_since(begin)>CHASE_FRAMERATE)
  {
    //Turn on the next pixel and turn off the previous one
    if(frame == LEN_CHASE_SEQ || frame == 0)
    {
      frame = 0;
      grid.setPixelColor(chase_lut[frame], c);
      grid.setPixelColor(chase_lut[LEN_CHASE_SEQ-1], BLACK);
      frame++;
    }
    else
    {
      grid.setPixelColor(chase_lut[frame], c);
      grid.setPixelColor(chase_lut[frame-1], BLACK);
      frame++;
    }

    //Reset the counter
    begin = millis();
  }
  grid.show();
}

//****************************************
//Make all of the pixels "breath" together
void fade_pixels(uint32_t c)
{
  uint8_t i;

  //************************************
  //Initialise if this is our first pass
  if(state_transition_flag == 1)
  {
    state_transition_flag = 0;
    begin = millis();
    frame = 0;
  }

  //******************************************
  //Update our animation at the set frame rate
  if(time_since(begin)>FADE_FRAMERATE)
  {
    //************************************************************************************
    //Set the color every time - We need this because of how the brightness function works
    for(i=0; i<grid.numPixels(); i++)
    {
      grid.setPixelColor(i, c);
    }

    //********************
    //Adjust the intensity
    grid.setBrightness(fade_lut[frame++]);

    //*****************
    //Loop the sequence
    if(++frame >= LEN_FADE_SEQ)
    {
      frame = 0;
    }

    begin = millis();
  }
  grid.show();
}

//***********************************************************
// Run through the lighting sequence for a docked board alert
void docked_sequence(void)
{
  //**********************************************
  //Check if enough time has passed between frames
  if(time_since(begin) < DOCK_FRAMERATE)
  {
    return;
  }
  begin = millis();

  //*****************************************
  //Check if we're just starting the sequence
  if(mode_transition_flag)
  {
    grid.setBrightness(grid_brightness);
    mode_transition_flag = 0;
    frame = 0;
  }

  //***************************************
  //Check if we have completed the sequence
  if(frame >= LEN_DOCKED_SEQ)
  {
    if(++repeat >= REPS_DOCKED_SEQ)
    {
      ALERT_MODE = NORMAL;
      repeat = 0;
      mode_transition_flag = 1;
      state_transition();
    }
    else
    {
      frame=0;
    }
    return;
  }

  //**********************
  //Implement the sequence
  for(uint8_t i=0; i<grid.numPixels(); i++)
  {
    grid.setPixelColor(pixel_map[i],docked_lut[frame][i]);
  }
  grid.show();
  frame++;
  return;
}

//********************************************
//Run through the lighting sequence for alert1
void alert1_sequence(void)
{
  //**********************************************
  //Check if enough time has passed between frames
  if(time_since(begin) < ALERT1_FRAMERATE)
  {
    return;
  }
  begin = millis();

  //*****************************************
  //Check if we're just starting the sequence
  if(mode_transition_flag)
  {
    grid.setBrightness(grid_brightness);
    mode_transition_flag = 0;
    frame = 0;
    begin = millis();
  }

  //***************************************
  //Check if we have completed the sequence
  if(frame >= LEN_ALERT1_SEQ)
  {
    if(++repeat >= REPS_ALERT1_SEQ)
    {
      ALERT_MODE = NORMAL;
      repeat = 0;
      mode_transition_flag = 1;
      state_transition();
    }
    else
    {
      frame=0;
    }
    return;
  }

  //**********************
  //Implement the sequence
  for(uint8_t i=0; i<grid.numPixels(); i++)
  {
    grid.setPixelColor(pixel_map[i],alert1_lut[frame][i]);
  }
  grid.show();
  frame++;
  return;
}

//********************************************
//Run through the lighting sequence for alert2
void alert2_sequence(void)
{
  //**********************************************
  //Check if enough time has passed between frames
  if(time_since(begin) < ALERT2_FRAMERATE)
  {
    return;
  }
  begin = millis();

  //*****************************************
  //Check if we're just starting the sequence
  if(mode_transition_flag)
  {
    grid.setBrightness(grid_brightness);
    mode_transition_flag = 0;
    frame = 0;
    begin = millis();
  }

  //***************************************
  //Check if we have completed the sequence
  if(frame >= LEN_ALERT2_SEQ)
  {
    if(++repeat >= REPS_ALERT2_SEQ)
    {
      ALERT_MODE = NORMAL;
      repeat = 0;
      mode_transition_flag = 1;
      state_transition();
    }
    else
    {
      frame=0;
    }
    return;
  }

  //**********************
  //Implement the sequence
  for(uint8_t i=0; i<grid.numPixels(); i++)
  {
    grid.setPixelColor(pixel_map[i],alert2_lut[frame][i]);
  }
  grid.show();
  frame++;
  return;
}

//********************************************
//Run through the lighting sequence for alert3
void alert3_sequence(void)
{
  //**********************************************
  //Check if enough time has passed between frames
  if(time_since(begin) < ALERT3_FRAMERATE)
  {
    return;
  }

  //*****************************************
  //Check if we're just starting the sequence
  if(mode_transition_flag)
  {
    mode_transition_flag = 0;
    frame = 0;
    repeat = 0;
    color = 0;
    begin = millis();
  }
  begin = millis();

  //**********************
  //Set the sequence color
  for(uint8_t i=0; i<grid.numPixels(); i++)
  {
    if(color%2)
    {
      if(alert3_lut[1][i] >= 1)   //Outside square
      {
        grid.setPixelColor(pixel_map[i],alert3_color_lut[color]);
      }
      else
      {
        grid.setPixelColor(pixel_map[i],0x000000);
      }
    }
    else
    {
      if(alert3_lut[0][i] >= 1)   //Inside square
      {
        grid.setPixelColor(pixel_map[i],alert3_color_lut[color]);
      }
      else
      {
        grid.setPixelColor(pixel_map[i],0x000000);
      }
    }
  }
  //*****************
  //Fade the sequence
  grid.setBrightness(fade_lut[frame++]);
  grid.show();

  //*****************
  //Loop the sequence
  if(++frame >= LEN_FADE_SEQ)
  {
    frame = 0;
    if(++color >= COLORS_ALERT3_SEQ)
    {
      color = 0;
      //***************************************
      //Check if we have completed the sequence
      if(++repeat >= REPS_ALERT3_SEQ)
      {
        ALERT_MODE = NORMAL;
        repeat = 0;
        mode_transition_flag = 1;
        state_transition();
      }
    }
  }

  return;
}

//*****************************************************
//Run through the lighting sequence for a claimed alert
void claim_sequence(void)
{
  //**********************************************
  //Check if enough time has passed between frames
  if(time_since(begin) < FADE_FRAMERATE)
  {
    return;
  }

  //*****************************************
  //Check if we're just starting the sequence
  if(mode_transition_flag)
  {
    mode_transition_flag = 0;
    frame = 0;
  }

  //***************************************
  //Check if we have completed the sequence
  if(frame >= LEN_FADE_SEQ)
  {
    ALERT_MODE = NORMAL;
    mode_transition_flag = 1;
    state_transition();
    return;
  }

  //**********************
  //Implement the sequence
  if(time_since(begin)>FADE_FRAMERATE)
  {
    //************************************************************************************
    //Set the color every time - We need this because of how the brightness function works
    for(uint8_t i=0; i<grid.numPixels(); i++)
    {
      grid.setPixelColor(i, grid.Color(0,200,0));
    }

    //********************
    //Adjust the intensity
    grid.setBrightness(fade_lut[frame++]);

    begin = millis();
    grid.show();
  }
  return;
}

//*******************************************
//The function that runs your custom sequence
void custom_sequence(void)
{
  //**********************************************
  //Check if enough time has passed between frames
  if(time_since(begin) < custom_animation_framerate)
  {
    return;
  }

  //*****************************************
  //Check if we're just starting the sequence
  if(state_transition_flag)
  {
    grid.setBrightness(grid_brightness);
    state_transition_flag = 0;
    frame = 0;
  }
  begin = millis();

  //*****************************************
  //Update the LEDs to display the next frame
  for(uint8_t i=0; i<grid.numPixels(); i++)
  {
    grid.setPixelColor(pixel_map[i],custom_animation_lut[frame][i]);
  }
  grid.show();

  //*********************************************************************
  //Set the animation to loop by starting from the beginning once it ends
  if(++frame >= custom_animation_length)
  {
    frame = 0;
  }

  return;
}

//********************************
//Just say hello every few minutes
void startup_display()
{
    if(state_transition_flag)
    {
      state_transition_flag = 0;
      reminder_time = millis();
    }

    if(time_since(reminder_time) > ALERT2_DELAY)
    {
      ALERT_MODE = ALERT2;
      reminder_time = millis();
    }
}
//**************************************************
//Return the number of milliseconds since start_time
uint32_t time_since(uint32_t start_time)
{
  return(millis()-start_time);
}
