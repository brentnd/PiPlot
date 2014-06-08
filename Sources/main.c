#include "Config.h"
#include <string.h>
#include <stdlib.h>

#define MOVE_DIST 10
#define BUF_SIZE  50

#define CR  13
#define BS  8

char* buffer;
char* p_buffer;

void ProcessCommand()
{
  uint32_t x[2];
  char *split;
  int i = 0;
  p_buffer = &buffer[0];
  split = strtok(p_buffer," ,");
  while( (split != NULL) & (i<2) )
  {
    x[i++] = atoi(split);
    split = strtok( NULL, " ,");
  }
  if(x[0] == 0 & x[1] == 0)
  {
    PRINTLN("Exit G-code Mode");
    return;
  }
  if(((x[0]+x[1]) < 100) | ((x[0]+x[1]) > 800))
  {
    PRINTLN("Bad coordinates");
  }
  else
  {
    printf("Going to: (%d, %d)\n\r",x[0],x[1]);
    MoveToAbsolute(x[0],x[1]);
    PRINTLN("Done");
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
      LINEFEED;
      ProcessCommand();
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
