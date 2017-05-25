#ifndef CMD_H_
#define CMD_H_

#include <string.h>

#undef HACKPACK_DEBUG
//#define HACKPACK_DEBUG

#define COM1    "9ad400dcc92f"
#define COM2    "1536781a44ed"
#define COM_CD  "98F65O"

//*************
//Block options
extern uint8_t block_scale;
extern uint8_t block_glow;
extern uint8_t block_jitter;

//*******
int parse_command(String command);
uint8_t send_packet(void);
String search_string(String data, char delimiter, int index);
void awake(uint8_t cmd);

#endif
