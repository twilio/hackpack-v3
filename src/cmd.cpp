#include "states.h"
#include "pixel_grid.h"
#include "cmd.h"

uint8_t block_scale = 1;
uint8_t block_glow = 0;
uint8_t block_jitter = 0;

//****************************
// Handle the incoming message
int parse_command(String command)
{
    #ifdef HACKPACK_DEBUG
      Serial.println(command);
    #endif

    String cmd_str = search_string(command, ',', 0);

    if(cmd_str == "")
    {
      #ifdef HACKPACK_DEBUG
          Serial.println("Invalid Command!!");
      #endif
      return(1);
    }

    //****************************
    //Check which command was sent
    if(cmd_str == "color")
    {
        String red_str = search_string(command, ',', 1);
        String green_str = search_string(command, ',', 2);
        String blue_str = search_string(command, ',', 3);
        String bright_str = search_string(command, ',', 4);

        //********************************************
        //Do some basic error checking of the commands
        if(red_str == "" || green_str == "" || blue_str == "")
        {
            #ifdef HACKPACK_DEBUG
                Serial.println("Invalid Argument!!");
                Serial.println(red_str);
                Serial.println(green_str);
                Serial.println(blue_str);
            #endif
            return(1);
        }

        //*****************
        //Extract the color
        uint8_t red = red_str.toInt();
        uint8_t green = green_str.toInt();
        uint8_t blue = blue_str.toInt();
        grid_color = grid.Color(red, green, blue);

        //If we're in startup mode then switch to block mode
        if(CURRENT_STATE == STARTUP)
        {
          CURRENT_STATE = BLOCK;
        }
        state_transition();
    }
    else if (cmd_str == "brightness")
    {
      String bright_str = search_string(command, ',', 1);

      //****************************
      //Check for a brightness value
      if(bright_str == "")
      {
        grid_brightness = 0;      //Set to 0 to ignore
        #ifdef HACKPACK_DEBUG
            Serial.println("Invalid Argument!!");
        #endif
      }
      else
      {
        grid_brightness = bright_str.toInt();
        state_transition();
      }
    }
    else if(cmd_str == "claim")
    {
        ALERT_MODE = CLAIM;
        state_transition();
    }
    else if(cmd_str == "block")
    {
        CURRENT_STATE = BLOCK;
        state_transition();
    }
    else if(cmd_str == "fade")
    {
        CURRENT_STATE = FADE;
        state_transition();
    }
    else if(cmd_str == "chase")
    {
        CURRENT_STATE = CHASE;
        state_transition();
    }
    else if (cmd_str == "alert2")
    {
        ALERT_MODE = ALERT1;
        state_transition();
    }
    else if (cmd_str == "alert3")
    {
        ALERT_MODE = ALERT3;
        state_transition();
    }
    else if (cmd_str == "custom")
    {
        CURRENT_STATE = CUSTOM;
        state_transition();
    }
    else if (cmd_str == "docked")
    {
        ALERT_MODE = DOCKED;
        state_transition();
    }
    else if (cmd_str == "wake")
    {
        awake(1);
    }
    else if (cmd_str == "sleep")
    {
        awake(0);
    }
    else
    {
      return(1);
    }

    return 0;
}

//*********************************************
void wake_handler(const char* sub, const char* val)
{
  #ifdef HACKPACK_DEBUG
    Serial.print("Wake Handler- ");
    Serial.print(sub);
    Serial.print(" - ");
    Serial.println(val);
  #endif

  if(!strcmp(sub,COM1))
  {
    if(!strcmp(val,COM_CD))
    {
      ALERT_MODE = ALERT3;
      state_transition();
    }
  }
  else if(!strcmp(sub,COM2))
  {
    if(!strcmp(val,COM_CD))
    {
      ALERT_MODE = ALERT1;
      state_transition();
    }
  }
}
//*******************************************************************
//Identify when we connect to the pedestal and reply with serial data
void serialEvent1()
{
    uint8_t docked = 0;
    uint8_t polled = 0;

    //Read all of the available data
    while(Serial1.available())
    {
      char c = Serial1.read();
      #ifdef HACKPACK_DEBUG
        digitalWrite(D7, !digitalRead(D7));
        Serial.print(c);
      #endif
      if(c == 'd')
      {
        docked++;
      }
      else if (c == 'p')
      {
        polled++;
      }
      else
      {
        docked = 0;
        polled = 0;
      }
    }
    #ifdef HACKPACK_DEBUG
      Serial.println();
    #endif
    //********************************
    //Reply if this was a poll request
    if(polled == 3)
    {
      //Set serial sending mode on the dock
      digitalWrite(B2, HIGH);

      //Send the data block
      send_packet();

      //Wait until all of the data is sent
      Serial1.flush();

      //Set serial listening mode on the dock
      digitalWrite(B2, LOW);
    }

    //*************************************
    //Display the docked alert if neccesary
    if(docked == 3)
    {
      ALERT_MODE = DOCKED;
    }
}

//****************************************************
//Send data to the dock to display on the large screen
// Packet Structure: DeviceID,Command,Scale,Glow,Jitter,X,Y,R,G,B,R,G,B,....
uint8_t send_packet(void)
{
    uint8_t i;
    SYSTEM_STATE current_state = CURRENT_STATE;   //Regardless of what MODE we are in always send the current state

    String DeviceID = System.deviceID();

    //Print the device ID over Serial
    Serial1.print(DeviceID);
    Serial1.print(",");

    //Send the command
    switch(current_state)
    {
      case(STARTUP):
          Serial1.print("startup");
      break;
      case(BLOCK):
          Serial1.print("block");
      break;
      case(CHASE):
          Serial1.print("chase");
      break;
      case(FADE):
          Serial1.print("fade");
      break;
      case(CUSTOM):
          Serial1.print("custom");
      break;
      default:
          Serial1.print("unknown");
      break;
    }
    Serial1.print(",");

    //Send the block scale
    Serial1.print(block_scale);
    Serial1.print(",");

    //Send the block glow flag
    Serial1.print(block_glow);
    Serial1.print(",");

    //Send the block jitter flag
    Serial1.print(block_jitter);
    Serial1.print(",");

    //We don't need to change the co-ordinates but you could.... full x,y resolution is 76x25
    Serial1.print("-1,-1,");

    //Send the individual pixels
    for(i=0; i<PIXEL_COUNT; i++)
    {
        uint32_t RGB = grid.getPixelColor(i);
        Serial1.print((RGB >> 16) & 0xff);
        Serial1.print(",");
        Serial1.print((RGB >> 8) & 0xff);
        Serial1.print(",");
        Serial1.print(RGB & 0xff);
        Serial1.print(",");
    }
    Serial1.println();
}

//******************************************************************************************
//Search for delimiter separated values within a string - used for parsing incoming commands
String search_string(String data, char delimiter, int index)
{
    uint8_t i;
    uint8_t found = 0;
    int8_t strIndex[] = {0, -1};
    uint8_t maxIndex = data.length()-1;

    //***************************************
    //Search for delimiters within the string
    for(i=0; i<=maxIndex && found<=index; i++)
    {
      if(data.charAt(i)==delimiter || i==maxIndex)
      {
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
      }
    }

    //***********************
    //If we found a delimiter
    if(found>index)
    {
      return(data.substring(strIndex[0], strIndex[1]));
    }
    else
    {
      return("");
    }
}

void awake(uint8_t cmd)
{
  if(cmd)
  {
    Particle.subscribe("9ad400dcc92", wake_handler);
    Particle.subscribe("1536781a44e", wake_handler);
  }
  else
  {
    Particle.unsubscribe();
  }
}
