#ifndef STATES_H_
#define STATES_H_

#include <stdint.h>

//************
//System state
typedef enum states
{
  STARTUP,
  BLOCK,
  CHASE,
  FADE,
  CUSTOM
}SYSTEM_STATE;

extern SYSTEM_STATE CURRENT_STATE;
extern uint8_t state_transition_flag;

//****************************************************************
//System display mode - these are independent of the current state
//The display mode overrides the display for the current state
typedef enum modes
{
  NORMAL,
  ALERT1,
  ALERT2,
  ALERT3,
  CLAIM,
  DOCKED
}SYSTEM_MODE;

extern SYSTEM_MODE ALERT_MODE;
extern uint8_t mode_transition_flag;

void init_system(void);
void update_display(void);
void run_display_state(void);
void display_state(void);
uint8_t alert_mode(void);
void state_transition(void);

#endif
