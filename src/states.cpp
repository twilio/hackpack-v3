#include "application.h"
#include "states.h"
#include "cmd.h"
#include "pixel_grid.h"

uint8_t state_transition_flag = 1;
uint8_t mode_transition_flag = 1;

SYSTEM_STATE CURRENT_STATE = STARTUP;
SYSTEM_MODE ALERT_MODE = NORMAL;

//**********************************************
//Setup our serial ports and our cloud functions
void init_system(void)
{
  init_pixels();

  #ifdef HACKPACK_DEBUG
    Serial.begin(9600);
    Serial.println("Hello!!");
  #endif

  //Setup the dock serial port
  Serial1.begin(115200, SERIAL_8N1);
  Serial1.flush();

  //Set dock comm chip to listening mode
  pinMode(B2, OUTPUT);
  digitalWrite(B2, LOW);

  //Connect to the cloud
  Particle.connect();

  // Expose our functions to the particle server
  Particle.function("set_pixels", parse_command);

}

//*****************************************
//Update the animation on the Neopixel grid
void update_display(void)
{
  if(!alert_mode())
  {
    run_display_state();
  }
  return;
}

//****************************************************************************
//If we're in an alert mode it takes priority over our current animation state
//These modes are temporary modes and are agnostic of the actual state
//Return 0 if we're not in a temporary state
uint8_t alert_mode(void)
{
  switch(ALERT_MODE)
  {
    case(DOCKED):
      docked_sequence();
      return(1);
    break;
    case(ALERT1):
      alert1_sequence();
      return(1);
    break;
    case(CLAIM):
      claim_sequence();
      return(1);
    break;
    case(ALERT2):
      alert2_sequence();
      return(1);
    break;
    case(ALERT3):
      alert3_sequence();
      return(1);
    break;
    default:
      return(0);
    break;
  }
}

//*****************************************
//Handle our actual animation state machine
void run_display_state(void)
{
  switch(CURRENT_STATE)
  {
    //*************************
    case(STARTUP):
      startup_display();
    break;
    //*************************
    case(BLOCK):
      if(state_transition_flag)
      {
        set_all_pixels(grid_color, grid_brightness);
        state_transition_flag = 0;
      }
    break;
    //*************************
    case(CHASE):
      chase_pixels(grid_color);
    break;
    //*************************
    case(FADE):
      fade_pixels(grid_color);
    break;
    //*************************
    case(CUSTOM):
      custom_sequence();
    break;
  }
  return;
}

//********************************************************************
//Clear the display and set the flag if a state transition has occured
void state_transition(void)
{
  set_all_pixels(BLACK, 0);
  delay(10);                    //TODO see if we can reduce this delay
  state_transition_flag = 1;
}
