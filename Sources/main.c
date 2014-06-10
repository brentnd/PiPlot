#include "Config.h"
#include <string.h>
#include <stdlib.h>

#define MOVE_DIST 10
#define BUF_SIZE  50

#define MIN_BOUND     40
#define MAX_BOUND     360

#define CR  13
#define BS  8

#define GCODE_STATUS  uint8
#define GCODE_OK      0
#define GCODE_ERROR   1
#define GCODE_DONE    2
#define GCODE_PAUSE   3

char* buffer;
char* p_buffer;


GCODE_STATUS ProcessCommand()
{
  uint32_t x[2];
  char *split;
  int i = 0;
  // Redirect pointer to beginning
  p_buffer = &buffer[0];
  
  // Terminate
  if(strcmp( p_buffer, "end" ))
  {
    PRINTLN("EXIT G-code mode");
    return GCODE_DONE;
  }
  // Paused
  else if(strcmp( p_buffer, "pause") )
  {
    PRINTLN("G-code PAUSE");
    return GCODE_PAUSE;
  }
  
  // Else parse goto command
  split = strtok(p_buffer,"g ,");
  while( (split != NULL) & (i<2) )
  {
    x[i++] = atoi(split);
    split = strtok( NULL, "g ,");
  }
  // Check bounds
  if((x[0] < MIN_BOUND) | (x[0] > MAX_BOUND) | (x[1] < MIN_BOUND) | (x[1] > MAX_BOUND))
  {
    PRINTLN("Bad coordinates");
    return GCODE_ERROR;
  }
  else
  {
    printf("Going to: (%d, %d)\n\r",x[0],x[1]);
    MoveToAbsolute(x[0],x[1]);
    PRINTLN("Done");
    return GCODE_OK;
  }
}

void PGcode()
{
  for(;;)
  {
    /* Get a character */
    while(UART_getchar_present() == 0);
    (*p_buffer) = UART_getchar();
    UART_putchar((*p_buffer));
    (*(p_buffer+sizeof(char))) = 0;
    
    if((*p_buffer) == BS)
      p_buffer -= sizeof(char);
    /* Check for end of command */
    if((*p_buffer) == CR)
    {
      GCODE_STATUS st;
      LINEFEED;
      st = ProcessCommand();
      if(st == GCODE_DONE)
        break;
      p_buffer = &buffer[0]-(sizeof(char));
    }
    
    /* Go for next char */
    if(p_buffer < buffer+BUF_SIZE*sizeof(char))
      p_buffer += sizeof(char);
    else
    {
      LINEFEED;
      PRINTLN("Buffer overflow");
      PRINTLN("Returning to terminal");
      break;
    }
  }
}

void terminal()
{
  char c = 48;
  for(;;)
  {
    LINEFEED;
    UART_putchar('>');
    while(UART_getchar_present() == 0);
    c = UART_getchar();
    
    switch(c)
    {
    case 'w':
      PRINTLN("Moving UP");
      MoveY(-MOVE_DIST);
      break;
    case 's':
      PRINTLN("Moving DOWN");
      MoveY(MOVE_DIST);
      break;
    case 'a':
      PRINTLN("Moving LEFT");
      MoveX(-MOVE_DIST);
      break;
    case 'd':
      PRINTLN("Moving RIGHT");
      MoveX(MOVE_DIST);
      break;
    case 'h':
      PRINTLN("Going Home...");
      MoveHome();
      break;
    case 'z':
      PRINTLN("Zeroed at current position.");
      MoveSetZero();
      break;
    case 'g':
      PRINTLN("Entering Pseudo G-Code mode.");
      PGcode();
      break;
    case 'o':
      PRINTLN("Draw a circle?");
      DrawCircle(50);
      break;
    }
  }
  
}

/*
 * Future main method for Pythagorian Plotter
 */
int main(void)
{
  
  /* Initialize buffer */
  buffer = malloc( sizeof(char) * (BUF_SIZE+1));
  p_buffer = &buffer[0];
  
  ConfigInitialize();
  printf("Pythagorian Plotter v1.0\n\n");
  printf("Initialized...\n");
  ConfigStart();
  printf("Started...\n");
  MoveSetZero();
  printf("Zeroed...\n");
  
  // Start terminal loop
  terminal();
  
  return 0;
}
